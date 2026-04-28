#ifndef ORDERPROCESSOR_H
#define ORDERPROCESSOR_H

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
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
            Ensures that the program runs without crashing by ensuring
             threads are finished before they are destroyed
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

        /**
            @brief Adds a manually created order to the processing queue.
            Receives order details from user input (typically from the menu),
             constructs an Order object, and adds it to the queue for later processing.
            Thread-safe - uses queueMutex to protect concurrent access.
            @param order Shared pointer to the Order object to be queued
        */
        void addOrder(std::shared_ptr<Order> order);

        /**
            @brief Displays all orders currently waiting in the queue.
            Iterates through the orderQueue and prints details of each order
             including Order ID, Product ID, and Quantity Requested.
            If the queue is empty, displays an appropriate message.
            Thread-safe - locks queueMutex before accessing the queue.
        */
        void displayQueue();

        /**
            @brief Processes all orders currently in the queue sequentially.
            Takes each order from the front of the queue, attempts to fulfill it
             using the shared InventoryManager, and adds the processed order
             to the orderHistory vector.
            Orders are removed from the queue after processing.
            Thread-safe - protects both the queue and history operations.
        */
        void processQueue();
    protected:

    private:
        std::shared_ptr<InventoryManager> inventory;
        std::vector<std::shared_ptr<Order>> orderHistory;
        std::mutex historyMutex;
        std::vector<std::thread> workerThreads;
        std::queue<std::shared_ptr<Order>> orderQueue;  // For manual orders
        std::mutex queueMutex;

        static constexpr int TOTAL_REQUIRED_ORDERS = 20;
        static constexpr int NUM_THREADS = 5;
        static constexpr int ORDERS_PER_THREAD = TOTAL_REQUIRED_ORDERS/NUM_THREADS;

        /**
            @brief The logic executed by each of the threads
            Attempts a random purchase, then adds to the orderHistory
             vector.
        */
        void threadWorkerFunc();
};

#endif // ORDERPROCESSOR_H
