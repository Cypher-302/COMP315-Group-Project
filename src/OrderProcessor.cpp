#include "OrderProcessor.h"
#include <iostream>
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
    // TODO

    //const int TOTAL_REQUIRED_ORDERS = 20;
    //const int ORDERS_PER_THREAD = TOTAL_REQUIRED_ORDERS / NUM_THREADS;

    // ^ These should be somewhere in the program, maybe a part of this
    //  class as member variables?
    // Could just keep const ORDERS_PER_THREAD in this function and const
    //  NUM_THREADS in runSimulation, but that feels too "magic-numbery"
}
