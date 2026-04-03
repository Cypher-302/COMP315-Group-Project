#include "../include/OrderProcessor.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

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
    const int NUM_THREADS = 5;

    // ensure the vector is empty for a new simulation
    workerThreads.clear();

    std::cout << "Beginning simulation with " << NUM_THREADS << " threads..." << std::endl;

    for (int i; i < NUM_THREADS; i++)
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
    // TODO
}

void OrderProcessor::threadWorkerFunc()
{

    for(int i = 0; i < ORDERS_PER_THREAD; i++){

        //generate a random productID
        int productId = rand() % 10 + 1;
        int quantity = rand() % 5 + 1;  //generates a random quantity

        //tries to fulfill the order against the shared inventory. 
        // returns true it there's sufficient stock
        bool success = inventory->processOrder(productId, quantity);

        //generates a unique Order ID across all threads
        static std::atomic<int> nextOrderID(1);

        //Construct the order record on the heap, the shared_ptr allows safety
        auto order = std::make_shared<Order>(nextOrderID++, productId, quantity, success);

        {
            std::lock_guard<std::mutex> lock(historyMutex);
            orderHistory.push_back(order);
        }
    }
}
