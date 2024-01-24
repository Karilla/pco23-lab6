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

int ComputationManager::requestComputation(Computation c) {
    monitorIn();
    if(bufferSize >= MAX_TOLERATED_QUEUE_SIZE){
        wait(accessBuffer);
    }
    bufferSize++;
    unsigned int id = nextId;
    Request req (c, nextId++);
    buffer[c.computationType].push_front(req);
    monitorOut();
    return id;
}

void ComputationManager::abortComputation(int id) {
    // TODO
}

Result ComputationManager::getNextResult() {
    monitorIn();

    while(results.empty() or results.front().getId() != expectedResult){
        wait(emptyResult);
        results.sort();
    }

    Result result = results.front();

    results.pop_front();

    monitorOut();

    return result;
}

Request ComputationManager::getWork(ComputationType computationType) {
    monitorIn();
    if(buffer[computationType].empty()){
        wait(conditionsComputationType[(int)computationType]);
    }
    Request newReq = buffer[computationType].front();
    buffer[computationType].pop_front();
    results.emplace_front(newReq.getId(),std::nullopt);
    monitorOut();

    return newReq;
}

bool ComputationManager::continueWork(int id) {
    // TODO
    return true;
}

void ComputationManager::provideResult(Result result) {
    monitorIn();
    auto it = std::find_if(results.begin(), results.end(),
                           [&](const auto& pairIdResult){ return pairIdResult.first == result.getId();});
    if(it == results.end()){
       monitorOut();
       return;
    }
    it->second = result;
    signal(emptyResult);
    monitorOut();
}

void ComputationManager::stop() {
    // TODO
}
