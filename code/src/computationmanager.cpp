//     ____  __________     ___   ____ ___  _____ //
//    / __ \/ ____/ __ \   |__ \ / __ \__ \|__  / //
//   / /_/ / /   / / / /   __/ // / / /_/ / /_ <  //
//  / ____/ /___/ /_/ /   / __// /_/ / __/___/ /  //
// /_/    \____/\____/   /____/\____/____/____/   //
// Auteurs : Prénom Nom, Prénom Nom


// A vous de remplir les méthodes, vous pouvez ajouter des attributs ou méthodes pour vous aider
// déclarez les dans ComputationManager.h et définissez les méthodes ici.
// Certaines fonctions ci-dessous ont déjà un peu de code, il est à remplacer, il est là temporairement
// afin de faire attendre les threads appelants et aussi afin que le code compile.

#include "computationmanager.h"
#include <iostream>
#include <algorithm>

ComputationManager::ComputationManager(int maxQueueSize): MAX_TOLERATED_QUEUE_SIZE(maxQueueSize)
{
}

int ComputationManager::nextId = 0;
int ComputationManager::expectedResult = 0;

// Cette méthode permet de demander d’effectuer un calcul et retourne un identifiant (id), donné
//par le buffer, correspondant au calcul.
int ComputationManager::requestComputation(Computation c) {
    monitorIn();
    // Si le buffer est plein, on attend
    auto type = static_cast<size_t>(c.computationType);
    if(buffer[c.computationType].size() >= MAX_TOLERATED_QUEUE_SIZE){
       if(stopped) {
          monitorOut();
          throwStopException();
       }
        wait(bufferFull);
       if(stopped) {
          signal(bufferFull);
          monitorOut();
          throwStopException();
       }
    }
    int id = nextId;
    Request req (c, nextId++);
    buffer[c.computationType].push_front(req);
    results.emplace_front(req.getId(), std::nullopt);
    signal(computationTypeEmpty[type]);
    monitorOut();
    return id;
}

// Cette méthode permet d’annuler un calcul en cours grâce à son identifiant.
void ComputationManager::abortComputation(int id) {

   monitorIn();
   // On cherche la requête dans le buffer et on la supprime si on la trouve
   for(auto& list : buffer){
      auto it = std::find_if(list.second.begin(), list.second.end(),
                             [&](const auto& request){ return request.getId() == id;});
      // Si la requête est trouvée
      auto type = static_cast<size_t>(list.first);
      if(it != list.second.end()){
         list.second.erase(it);
         signal(bufferFull);
         monitorOut();
         return;
      }
   }

   // On cherche si la requête est dans les résultats (i.e. en cours de calcul ou calculée)
   auto it = std::find_if(results.begin(), results.end(),
                          [&](const auto& pairIdResult){ return pairIdResult.first == id;});
   if(it != results.end()){
      // Si c'est un résultat en cours de calcul, on signale pour débloquer le thread qui l'attend
      if(!it->second.has_value() and it->first == expectedResult){
         expectedResult++;
         signal(emptyResult);
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
   //results.sort();
    // Si il n'y a pas de résultat ou que le résultat n'est pas celui attendu, on attend
    while(results.empty() /*or results.back().first != expectedResult*/ or !results.back().second.has_value()){
         if(stopped) {
             monitorOut();
             throwStopException();
         }
        wait(emptyResult);
         if(stopped) {
             signal(emptyResult);
             monitorOut();
             throwStopException();
         }
        //results.sort();
    }

    Result result = results.back().second.value();
    results.pop_back();
    expectedResult++;
    //std::cout << "Result " << result.getId() << " : " << expectedResult << std::endl;
    monitorOut();

    return result;
}

// Cette méthode permet au calculateur de demander du travail du type computationType,
//qu’il reçoit sous forme d’une requête de calcul.
Request ComputationManager::getWork(ComputationType computationType) {
    monitorIn();
    // Si il n'a a pas de computation du bon type dans le buffer, on attend
    if(buffer[computationType].empty()){
         if(stopped) {
            monitorOut();
            throwStopException();
         }
        wait(computationTypeEmpty[(int)computationType]);
         if(stopped) {
            signal(computationTypeEmpty[(int)computationType]);
            monitorOut();
            throwStopException();
         }
    }
    Request newReq = buffer[computationType].back();
    buffer[computationType].pop_back();
    signal(bufferFull);
    //results.emplace_front(newReq.getId(), std::nullopt);
    monitorOut();
    return newReq;
}

// Cette méthode permet au calculateur de demander s’il doit continuer à travailler sur le calcul
//avec l’identifiant donné.
bool ComputationManager::continueWork(int id) {
    monitorIn();
    if(stopped){
       std::cout << "Stopped" << std::endl;
       monitorOut();
       return false;
    }

    // Si le résultat n'est plus dans results
      auto it = std::find_if(results.begin(), results.end(),
                              [&](const auto& pairIdResult){ return pairIdResult.first == id;});

    monitorOut();
    return !(it == results.end());
}

// Cette méthode permet au calculateur de retourner le résultat du calcul.
void ComputationManager::provideResult(Result result) {
    monitorIn();
    auto it = std::find_if(results.begin(), results.end(),
                           [&](const auto& resultChecked){ return resultChecked.first == result.getId();});
    //std::cout << "provideResult: Result " << result.getId() << ", result found " << it->first<< std::endl;
    if(it == results.end()){
       monitorOut();
       return;
    }
    it->second = result;
    signal(emptyResult);
    monitorOut();
}

// la fonction stop() devra libérer tous les threads en attente sur le buffer et devra empêcher la mise en
//attente de tout thread lors d’un appel à une méthode du buffer après l’appel de stop().
void ComputationManager::stop() {

   monitorIn();
   stopped = true;
   // On signale sur toutes les conditions existantes
   signal(bufferFull);
   signal(emptyResult);
   //signal(notExpectedResult);
   for (auto &condition: computationTypeEmpty) {
      signal(condition);
   }

   monitorOut();
}
