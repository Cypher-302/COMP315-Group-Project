#include "../include/OrderProcessor.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <ctime>
#include <functional>

OrderProcessor::OrderProcessor(std::shared_ptr<InventoryManager> inv) : inventory(inv)
{
    // inventory pointer is now stored in the class memeber variable, all threads
    //  created by this class will use this shared pointer

    // orderHistory, workerThreads, and historyMutex are automatically instantiated
}

OrderProcessor::~OrderProcessor()
{
    for (auto &t : workerThreads)
    {
        // a thread MUST be joined before it is destroyed,
        //  as if it is destroyed while still active and not joined
        //  the program will be terminated
        if (t.joinable())
        {
            t.join();
        }
    }

    // no manual deletion is required, as orderHistory and inventory
    //  are smart pointers and automatically clean up their memory when
    //  they go out of scope
}

void OrderProcessor::runSimulation()
{
    // ensure the vector is empty for a new simulation
    workerThreads.clear();

    std::cout << "Beginning simulation with " << NUM_THREADS << " threads..." << std::endl;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        // instantiates a new workerThread at the back of the workerThreads vector
        workerThreads.emplace_back(&OrderProcessor::threadWorkerFunc, this);
    }

    for (std::thread &t : workerThreads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    std::cout << "Simulation complete.\n" << std::endl;
}

void OrderProcessor::displayHistory()
{
    std::cout << "\n--- FINAL ORDER HISTORY SUMMARY ---" << std::endl;

    if (orderHistory.empty()) // check if orderHistory vector empty to avoid errors
    {
        std::cout << "No orders were processed." << std::endl;
        return;
    }

    std::lock_guard<std::mutex> lock(historyMutex);
    for (const auto &orderPtr : orderHistory)
    {
        if (orderPtr) // check orderPtr is not null
        {
            std::string statusStr = orderPtr->getOrderStatus() ? "SUCCESS" : "FAILED";

            std::cout << "Order ID: " << orderPtr->getOrderID()
                      << " | Product ID: " << orderPtr->getProductID()
                      << " | Qty: " << orderPtr->getQuantityRequested()
                      << " | Status: " << statusStr << std::endl;
        }
    }
    std::cout << "-----------------------------------\n" << std::endl;
}

void OrderProcessor::threadWorkerFunc()
{
    // give each thread a random, unique seed for the random function
    std::hash<std::thread::id> hasher;
    std::srand(std::time(nullptr) + hasher(std::this_thread::get_id()));

    for(int i = 0; i < ORDERS_PER_THREAD; i++){

        int randomProductId = 1 + rand() % 10; // generates a random productID [1,10]

        const int MIN_REQUEST_QUANTITY = -5; // effectively a restock
        const int MAX_REQUEST_QUANTITY = 15;

        int randomRequestedQuantity = MIN_REQUEST_QUANTITY + std::rand() % (MAX_REQUEST_QUANTITY - MIN_REQUEST_QUANTITY + 1);  // generates a random quantity [Min,Max]

        if (randomRequestedQuantity == 0) randomRequestedQuantity = 1;

        // tries to fulfill the order against the shared inventory.
        // returns true it there's sufficient stock
        bool success = inventory->processOrder(randomProductId, randomRequestedQuantity);

        // generates a unique Order ID across all threads
        static std::atomic<int> nextOrderID(1);

        // construct the order record on the heap, the shared_ptr allows safety
        auto order = std::make_shared<Order>(nextOrderID++, randomProductId, randomRequestedQuantity, success);

        {
            std::lock_guard<std::mutex> lock(historyMutex);
            orderHistory.push_back(order);
        }

        // forces the thread to sleep for a random time between 10ms and 50ms
        // simulates network delay and task processing speeds, shows interleaved output more clearly
        int sleepTime = 10 + (std::rand() % 41);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }
}
