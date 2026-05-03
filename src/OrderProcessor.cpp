#include "../include/OrderProcessor.h"
#include "../include/Utility.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <ctime>
#include <functional>
#include <random>

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

void OrderProcessor::addOrder(std::shared_ptr<Order> order){
     const int CENTER = 27;

    std::cout << std::endl;

     // Validate that the order pointer is not null
    if (!order) {
        Utility::printRep(' ', ' ', CENTER);
        std::cout << "Error: Cannot add null order to queue!" << std::endl;
        return;
    }

    // Lock the queue mutex to ensure thread-safe insertion
    std::lock_guard<std::mutex> lock(queueMutex);

    // Add the order to the back of the queue
    orderQueue.push(order);

    Utility::printRep(' ', ' ', CENTER);
    std::cout << "Order #" << order->getOrderID()
              << " added to queue successfully." << std::endl;
}

void OrderProcessor::displayQueue() {
    // Lock the queue to prevent modifications during display
    std::lock_guard<std::mutex> lock(queueMutex);

    // Check if queue is empty
    if (orderQueue.empty())
    {
        std::cout << "\n--- ORDER QUEUE ---" << std::endl;
        std::cout << "No orders are currently queued." << std::endl;
        std::cout << "-------------------\n" << std::endl;
        return;
    }

    // Display header
    std::cout << "\n--- ORDER QUEUE (" << orderQueue.size() << " orders) ---" << std::endl;
    std::cout << "Pos | Order ID | Product ID | Quantity | Status" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    // We need to make a copy to iterate since queue's don't support iteration
    std::queue<std::shared_ptr<Order>> tempQueue = orderQueue;
    int position = 1;

    // Display each order in the queue
    while (!tempQueue.empty())
    {
        auto order = tempQueue.front();
        tempQueue.pop();

        if (order)
        {
            std::string statusStr = order->getOrderStatus() ? "Processed" : "Pending";

            std::cout << " " << position << "   | "
                      << order->getOrderID() << "        | "
                      << order->getProductID() << "          | "
                      << order->getQuantityRequested() << "        | "
                      << statusStr << std::endl;
        }
        position++;
    }
    std::cout << "------------------------------------------------\n" << std::endl;
}

void OrderProcessor::processQueue()
{
    // check if the queue is empty before starting threads
    {
        // Lock the queue mutex for the entire processing operation
        // to prevent new orders being added while processing
        std::lock_guard<std::mutex> queueLock (queueMutex);

        if (orderQueue.empty())
        {
            std::cout << "No orders in queue to process." << std::endl;
            return;
        }

        std::cout << "\nProcessing " << orderQueue.size()
                    << " queued orders using " << NUM_THREADS
                    << " threads..." << std::endl;
    }

    // keep track of the processing and processing status of the orders
    // using atomic counters so multiple threads can increment them safely
    std::atomic<int> processed = 0;
    std::atomic<int> successful = 0;
    std::atomic<int> failed = 0;

    // define worker logic that each thread will execute
    // lambda function enables sharing local atomic variables and class members without defining new class method
    auto queueWorker = [&]()
    {
        while (true)
        {
            std::shared_ptr<Order> order = nullptr;

            // lock the queue only for time needed to pop an item
            {
                std::lock_guard<std::mutex> queueLock(queueMutex);
                if (orderQueue.empty()) {
                    break; // Queue is empty, exit this thread
                }
                order = orderQueue.front();
                orderQueue.pop();
            }

            if (!order) continue; // skips if null

            // process order
            bool success = inventory->processOrder(
                order->getProductID(),
                order->getQuantityRequested()
            );

            order->setOrderStatus(success);

            // safely update history, using mutex
            {
                std::lock_guard<std::mutex> historyLock(historyMutex);
                orderHistory.push_back(order);
            }

            // safely update atomic counters
            processed++;
            if (success) successful++;
            else failed++;
        }
    };

    // spawn threads to process queue
    std::vector<std::thread> queueThreads;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        queueThreads.emplace_back(queueWorker);
    }

    // wait for all threads to finish processing
    for (auto& t : queueThreads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    // display processing summary
    std::cout << "\nQueue processing complete!" << std::endl;
    std::cout << "Total processed: " << processed.load() << std::endl;
    std::cout << "Successful: " << successful.load() << std::endl;
    std::cout << "Failed: " << failed.load() << std::endl;

    // check remaining (should always be 0)
    std::lock_guard<std::mutex> finalLock(queueMutex);
    std::cout << "Remaining in queue: " << orderQueue.size() << "\n" << std::endl;
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
    thread_local std::mt19937 gen(std::hash<std::thread::id>{}(std::this_thread::get_id())); // give each thread a random, unique seed for the random function

    for(int i = 0; i < ORDERS_PER_THREAD; i++){
        std::uniform_int_distribution<> distID(1, 15);
        int randomProductId = distID(gen); // generates a random productID [1,15]


        const int MIN_REQUEST_QUANTITY = -5; // effectively a restock
        const int MAX_REQUEST_QUANTITY = 15;
        std::uniform_int_distribution<> distRequestQuantity(MIN_REQUEST_QUANTITY, MAX_REQUEST_QUANTITY);

        int randomRequestedQuantity = distRequestQuantity(gen);  // generates a random quantity [Min,Max]

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
