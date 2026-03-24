#ifndef ORDERPROCESSOR_H
#define ORDERPROCESSOR_H

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include "Order.h"
#include "InventoryManager.h"

class OrderProcessor final
{
    public:
        /**
            Constructs an OrderProcessor object with the following details.
            @param Pointer to the InventoryManager object to be used
        */
        OrderProcessor(std::shared_ptr<InventoryManager> inv);

        /**
            @brief Destructor

        */
        ~OrderProcessor();

        /**
            @brief Starting point for the multi-threaded simulation.
            Instantiates at least 5 std::thread objects, stores them in
            the workerThreads vector and ensures they all finish processing
        */
        void runSimulation();

        /**
            @brief Displays a final summary of the simulation.
            Displays the final status for all processed orders in the
            orderHistory vector
        */
        void displayHistory();
    protected:

    private:
        std::shared_ptr<InventoryManager> inventory;
        std::vector<std::shared_ptr<Order>> orderHistory;
        std::mutex historyMutex;
        std::vector<std::thread> workerThreads;

        /**
            @brief The logic executed by each of the threads
            Attempts a random purchase, then adds to the orderHistory
            vector.
        */
        void threadWorkerFunc();
};

#endif // ORDERPROCESSOR_H
