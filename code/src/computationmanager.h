/**
\file computationmanager.h
\author Eva Ray, Benoit Delay
\date 27.01.2024

Ce fichier contient la définition de plusieurs classes permettant l’exécution concurrente et différée de calculs.
En particulier, il contient la définition de la classe ComputationManager qui est un buffer partagé entre des clients
et des moteurs de calculs et qui est implémentée sous la forme d'un moniteur de Hoare.
*/

#ifndef COMPUTATIONMANAGER_H
#define COMPUTATIONMANAGER_H

#include <memory>
#include <forward_list>
#include <map>
#include <vector>
#include <queue>
#include <optional>
#include <list>

#include "pcosynchro/pcohoaremonitor.h"
#include "pcosynchro/pcoconditionvariable.h"
#include "pcosynchro/pcomutex.h"

/**
 * @brief The ComputationType enum represents the abstract computation types that are available
 */
enum class ComputationType {
   A, B, C
};

/**
 * @brief The Computation class Represents a computation with a given type and data.
 */
class Computation {
public:
   /**
    * @brief Computation Constructs a computation of a given type
    * @param computationType
    */
   Computation(ComputationType computationType) : computationType(
      computationType) { data = std::make_shared<std::vector<double>>(); }

   /**
    * @brief computationType The given type
    */
   ComputationType computationType;
   /**
    * @brief data The data for the computation
    */
   std::shared_ptr<std::vector<double>> data;

};

/**
 * @brief The Request class is a request for a computation with and id and data
 */
class Request {
public:
   Request() : data(nullptr) {}

   Request(std::shared_ptr<std::vector<double>> data, int id) : data(std::move(data)), id(id) {}

   Request(const Computation &c, int id) : data(c.data), id(id) {}

   [[nodiscard]] int getId() const { return id; }

   /**
    * @brief data The data for the computation
    */
   std::shared_ptr<const std::vector<double>> data;

private:
   int id{0};
};

/**
 * @brief The Result class holds a result and an id
 */
class Result {
public:
   Result(int id, double result) : id(id), result(result) {}

   [[nodiscard]] int getId() const { return id; }

   [[nodiscard]] double getResult() const { return result; }

   bool operator<(const Result &other) const {
      // Tri en fonction de l'attribut
      return id < other.id;
   }

private:
   int id;
   double result;
};

/**
 * @brief The ClientInterface class contains the methods of the buffer that are exposed to the client
 */
class ClientInterface {
public:
   /**
    * @brief requestComputation Request a computation c
    * @param c The computation to be done
    * @return The assigned id (should follow the order of the requests)
    */
   virtual int requestComputation(Computation c) = 0;

   /**
    * @brief abortComputation Allows the client to abort a computation
    * This should remove the Request/Result corresponding to the id in
    * the ComputationManager (buffer) if there is one and stop a compute
    * engine working on it if there was one.
    * @param id the id of the computation to be aborted
    */
   virtual void abortComputation(int id) = 0;

   /**
    * @brief getNextResult Method that provides the next result.
    * The order of the results must follow the order of the requests.
    * (order of ids of the results should follow the order of the request ids
    * which should follow the order of the requests).
    * @return The next Result of the requested computations
    */
   virtual Result getNextResult() = 0;
};

/**
 * @brief The ComputeEngineInterface class contains the methods of the buffer that are exposed to the compute engines
 */
class ComputeEngineInterface {
public:
   /**
    * @brief getWork is used to ask for work of a given type which will come as a Request
    * @param computationType the type of work that is wanted
    * @return a request to be fulfilled
    */
   virtual Request getWork(ComputationType computationType) = 0;

   /**
    * @brief continueWork Allows a compute engine to ask if it must continue working on a request
    * @param id the id of the request the compute engine is currently working on
    * @return true if the worker should continue working on the request with id id
    */
   virtual bool continueWork(int id) = 0;

   /**
    * @brief provideResult Allows a compute engine to prove a result to the buffer
    * @param result the result that has been computed
    */
   virtual void provideResult(Result result) = 0;
};

/**
 * @brief The ResultWithId struct is an id paired with an (optional) result.
 */
struct ResultWithId {

   /**
    * @brief ResultWithId Constructs a ResultWithId with an id and an optional result
    * @param id the id of the result
    * @param result the optional result
    */
   ResultWithId(int id, std::optional<Result> result) : id(id), result(result) {}

   int id;
   std::optional<Result> result;
};


/**
 * @brief The ComputationManager class is the implementation of the shared buffer between client and compute engines.
 * It is to be implemented as a Hoare monitor.
 */
class ComputationManager : public ClientInterface, public ComputeEngineInterface, protected PcoHoareMonitor {
public:
   /**
    * @brief The StopException class is an exception that is thrown when a thread tries to wait
    * when the buffer is stopped or is awoken (signaled) after the buffer is stopped.
    */
   class StopException : public std::exception {
   };

   /**
    * @brief ComputationManager Allows to create a buffer with a maximum queue size
    * @param maxQueueSize the maximum queue size allowed to store pending requests
    */
   ComputationManager(int maxQueueSize = 10);

   // Client Interface
   int requestComputation(Computation c) override;

   void abortComputation(int resultWithId) override;

   Result getNextResult() override;

   // Compute Engine Interface
   Request getWork(ComputationType computationType) override;

   bool continueWork(int id) override;

   void provideResult(Result resultChecked) override;


   // Control Interface
   /**
    * @brief stop Is used when the buffer is stopped, will release and interrupt waiting threads
    */
   void stop();

protected:

   // The maximum size of the buffer for each computation type
   const size_t MAX_TOLERATED_QUEUE_SIZE;
   // A map that maps a computation type to the list of requests for this type of computation
   std::map<ComputationType, std::list<Request>> buffer;
   // The list of results (or currently being computed results) with their id
   std::list<ResultWithId> results;
   // An array that stores the condition on which we should wait if the request queue is empty for each computation type
   std::array<Condition, 3> emptyQueuePerType;
   // An array that stores the condition on which we should wait if the request queue is full for each computation type
   std::array<Condition, 3> fullQueuePerType;
   // Condition on which we should wait if the result we are waiting for is not yet computed
   Condition notExpectedResult;
   // A boolean that is true if the app is terminated
   bool stopped;

private:
   /**
    * @brief throwStopException Throws a StopException (will be handled by the caller)
    */
   inline void throwStopException() { throw StopException(); }

   static int nextId;
};

#endif // COMPUTATIONMANAGER_H
