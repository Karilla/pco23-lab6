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


ComputationManager::ComputationManager(int maxQueueSize): MAX_TOLERATED_QUEUE_SIZE(maxQueueSize)
{
    // TODO
}

int ComputationManager::requestComputation(Computation c) {
    monitorIn();
    if(bufferSize >= MAX_TOLERATED_QUEUE_SIZE){
        wait(accessBuffer);
    }
    bufferSize++;
    Request req (c, id++);
    buffer[c.computationType].push_front(req);
    monitorOut();
    return id;
}

void ComputationManager::abortComputation(int id) {
    // TODO
}

Result ComputationManager::getNextResult() {
    // TODO
    // Replace all of the code below by your code

    // Filled with some code in order to make the thread in the UI wait
    monitorIn();

    monitorOut();

    return Result(-1, 0.0);
}

Request ComputationManager::getWork(ComputationType computationType) {
    monitorIn();
    if(buffer[computationType].empty()){
        //TODO: On attend
    }
    Request newReq = buffer[computationType].front();
    buffer[computationType].pop_front();
    monitorOut();

    return newReq;
}

bool ComputationManager::continueWork(int id) {
    // TODO
    return true;
}

void ComputationManager::provideResult(Result result) {
    // TODO
}

void ComputationManager::stop() {
    // TODO
}
