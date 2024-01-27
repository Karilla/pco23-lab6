/**
\file computationmanager.cpp
\author Eva Ray, Benoit Delay
\date 27.01.2024

Ce fichier contient l'implémentation de la classe ComputationManager qui permet l’exécution concurrente et
différée de calculs. Elle se présente sous la forme d'un buffer partagé entre des clients et des moteurs de calculs
et est implémentée sous la forme d'un moniteur de Hoare.
*/

#include "computationmanager.h"
#include <algorithm>

ComputationManager::ComputationManager(int maxQueueSize) : MAX_TOLERATED_QUEUE_SIZE(maxQueueSize), stopped(false) {
}

int ComputationManager::nextId = 0;

// Cette méthode permet de demander d’effectuer un calcul et retourne un identifiant (id), donné
// par le buffer, correspondant au calcul.
int ComputationManager::requestComputation(Computation c) {
   auto type = static_cast<size_t>(c.computationType);
   monitorIn();
   // If the queue is full for computationType, we wait
   if (buffer[c.computationType].size() >= MAX_TOLERATED_QUEUE_SIZE) {
      if (stopped) {
         monitorOut();
         throwStopException();
      }
      wait(fullQueuePerType[type]);
      if (stopped) {
         signal(fullQueuePerType[type]);
         monitorOut();
         throwStopException();
      }
   }
   int id = nextId;
   Request req(c, nextId++);
   buffer[c.computationType].push_front(req);
   results.emplace_front(req.getId(), std::nullopt);
   signal(emptyQueuePerType[type]);
   monitorOut();
   return id;
}

// Cette méthode permet d’annuler un calcul en cours grâce à son identifiant.
void ComputationManager::abortComputation(int id) {

   monitorIn();
   // We look for the request in the buffer containing the pending computations and delete it if we find it
   for (auto &list: buffer) {
      auto it = std::find_if(list.second.begin(), list.second.end(),
                             [&](const auto &request) { return request.getId() == id; });
      auto type = static_cast<size_t>(list.first);
      // If the request is found, we delete it
      if (it != list.second.end()) {
         list.second.erase(it);
         signal(fullQueuePerType[type]);
         monitorOut();
         return;
      }
   }

   // We check if the request is in the results (i.e. being computed or computed)
   auto it = std::find_if(results.begin(), results.end(),
                          [&](const auto &resultWithId) { return resultWithId.id == id; });
   if (it != results.end()) {
      // If it is a result being computed, we signal to unblock the thread that is potentially waiting for it
      if (!it->result.has_value()) {
         signal(notExpectedResult);
      }
      results.erase(it);
      monitorOut();
      return;
   }
}

// Cette méthode permet de demander les résultats au buffer. Les résultats seront retournés dans
//le même ordre que l’ordre des demandes de calcul. Cette méthode ne doit pas retourner les
//résultats de calculs qui ont été annulés. Elle est potentiellement bloquante.
Result ComputationManager::getNextResult() {
   monitorIn();
   // If there isn't any result or the result is not the one we are waiting for, we wait
   while (results.empty() or !results.back().result.has_value()) {
      if (stopped) {
         monitorOut();
         throwStopException();
      }
      wait(notExpectedResult);
      if (stopped) {
         signal(notExpectedResult);
         monitorOut();
         throwStopException();
      }
   }

   Result result = results.back().result.value();
   results.pop_back();
   monitorOut();
   return result;
}

// Cette méthode permet au calculateur de demander du travail du type computationType,
//qu’il reçoit sous forme d’une requête de calcul.
Request ComputationManager::getWork(ComputationType computationType) {
   auto type = static_cast<size_t>(computationType);
   monitorIn();
   // If there isn't any request of the right type in the buffer, we wait
   if (buffer[computationType].empty()) {
      if (stopped) {
         monitorOut();
         throwStopException();
      }
      wait(emptyQueuePerType[type]);
      if (stopped) {
         signal(emptyQueuePerType[type]);
         monitorOut();
         throwStopException();
      }
   }
   Request newReq = buffer[computationType].back();
   buffer[computationType].pop_back();
   signal(fullQueuePerType[type]);
   monitorOut();
   return newReq;
}

// Cette méthode permet au calculateur de demander s’il doit continuer à travailler sur le calcul
//avec l’identifiant donné.
bool ComputationManager::continueWork(int id) {
   monitorIn();
   if (stopped) {
      monitorOut();
      return false;
   }

   // We check if the result is in the results (i.e. being computed or computed)
   auto it = std::find_if(results.begin(), results.end(),
                          [&](const auto &pairIdResult) { return pairIdResult.id == id; });

   monitorOut();
   return !(it == results.end());
}

// Cette méthode permet au calculateur de retourner le résultat du calcul.
void ComputationManager::provideResult(Result result) {
   monitorIn();
   auto it = std::find_if(results.begin(), results.end(),
                          [&](const auto &resultChecked) { return resultChecked.id == result.getId(); });
   if (it == results.end()) {
      monitorOut();
      return;
   }
   it->result = result;
   signal(notExpectedResult);
   monitorOut();
}

// la fonction stop() devra libérer tous les threads en attente sur le buffer et devra empêcher la mise en
// attente de tout thread lors d’un appel à une méthode du buffer après l’appel de stop().
void ComputationManager::stop() {

   monitorIn();
   stopped = true;
   // We signal on every existing condition to unblock waiting threads
   signal(notExpectedResult);
   for (auto &condition: emptyQueuePerType) {
      signal(condition);
   }
   for (auto &condition: fullQueuePerType) {
      signal(condition);
   }
   monitorOut();
}
