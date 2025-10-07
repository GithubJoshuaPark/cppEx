#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <queue>
#include "helloEx.h" // for printLine
#include "multithreadingEx.h"

// --- Shared resources for the examples ---

// For race condition and mutex examples
int g_counter = 0;
std::mutex g_counter_mutex;

// For producer-consumer example
std::queue<int> g_data_queue;
std::mutex g_queue_mutex;
std::condition_variable g_queue_cv;
bool g_finished_producing = false;

// --- Worker Functions ---

/**
 * @brief A simple worker function that prints its ID.
 */
void simple_worker(int id) {
    std::cout << "  Worker thread " << id << " starting.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(50 * id));
    std::cout << "  Worker thread " << id << " finishing.\n";
}

/**
 * @brief Increments a global counter without protection, demonstrating a race condition.
 */
void unsafe_incrementer() {
    for (int i = 0; i < 10000; ++i) {
        // This is a "read-modify-write" operation and is NOT atomic.
        // Multiple threads can read the same value, all increment it, and then
        // write back, causing some increments to be lost.
        g_counter++;
    }
}

/**
 * @brief Increments a global counter safely using a mutex.
 */
void safe_incrementer() {
    for (int i = 0; i < 10000; ++i) {
        // std::lock_guard is an RAII-style mutex wrapper.
        // It locks the mutex on construction and automatically unlocks it
        // when the guard goes out of scope. This is the safest way to use a mutex.
        std::lock_guard<std::mutex> lock(g_counter_mutex);
        g_counter++;
    }
}

/**
 * @brief The producer thread: adds items to the shared queue.
 */
void producer() {
    for (int i = 0; i < 10; ++i) {
        {
            std::lock_guard<std::mutex> lock(g_queue_mutex);
            g_data_queue.push(i);
            std::cout << "  Produced: " << i << std::endl;
        } // Mutex is unlocked here
        g_queue_cv.notify_one(); // Notify one waiting consumer thread
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Signal that production is finished
    {
        std::lock_guard<std::mutex> lock(g_queue_mutex);
        g_finished_producing = true;
    }
    g_queue_cv.notify_all(); // Wake up all consumers to let them exit
}

/**
 * @brief The consumer thread: takes items from the shared queue.
 */
void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(g_queue_mutex);
        // The wait function will atomically unlock the mutex and wait.
        // It waits until the lambda returns true (i.e., the queue is not empty
        // or production is finished). When woken up, it re-locks the mutex.
        g_queue_cv.wait(lock, [] { return !g_data_queue.empty() || g_finished_producing; });

        if (!g_data_queue.empty()) {
            int data = g_data_queue.front();
            g_data_queue.pop();
            lock.unlock(); // Unlock before processing to allow other threads to work
            std::cout << "    Consumer " << id << " consumed: " << data << std::endl;
        } else if (g_finished_producing) {
            // Queue is empty and producer is done, so we can exit.
            break;
        }
    }
}

void multithreadingEx(void) {
    printLine("Multithreading Example");

    // --- 1. Basic Threading ---
    std::cout << "--- 1. Basic Threading ---\n";
    std::thread t1(simple_worker, 1);
    std::thread t2(simple_worker, 2);
    std::cout << "  Main thread waiting for workers to finish...\n";
    t1.join(); // The main thread blocks here until t1 completes.
    t2.join(); // The main thread blocks here until t2 completes.
    std::cout << "  Workers have finished.\n\n";

    // --- 2. Race Condition ---
    std::cout << "--- 2. Race Condition ---\n";
    g_counter = 0;
    std::vector<std::thread> unsafe_threads;
    for (int i = 0; i < 10; ++i) {
        unsafe_threads.emplace_back(unsafe_incrementer);
    }
    for (auto& t : unsafe_threads) { t.join(); }
    std::cout << "  Unsafe counter result: " << g_counter << " (Expected 100000, but likely less)\n\n";

    // --- 3. Mutex to Fix Race Condition ---
    std::cout << "--- 3. Mutex Synchronization ---\n";
    g_counter = 0;
    std::vector<std::thread> safe_threads;
    for (int i = 0; i < 10; ++i) {
        safe_threads.emplace_back(safe_incrementer);
    }
    for (auto& t : safe_threads) { t.join(); }
    std::cout << "  Safe counter result: " << g_counter << " (Correctly synchronized)\n\n";

    // --- 4. Producer-Consumer with Condition Variable ---
    std::cout << "--- 4. Producer-Consumer ---\n";
    std::thread producer_thread(producer);
    std::vector<std::thread> consumer_threads;
    for (int i = 0; i < 3; ++i) {
        consumer_threads.emplace_back(consumer, i + 1);
    }
    producer_thread.join();
    for (auto& t : consumer_threads) { t.join(); }
    std::cout << "  Producer and consumers have finished.\n";

    printLine("Multithreading Example Completed");
}