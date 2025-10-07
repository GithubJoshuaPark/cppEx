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
    // 1. 10개의 데이터를 순차적으로 생성합니다.
    for (int i = 0; i < 10; ++i) {
        {
            // 2. 'g_queue_mutex'를 잠급니다.
            //    std::lock_guard는 이 블록({})이 끝날 때 자동으로 잠금을 해제하여 편리하고 안전합니다.
            std::lock_guard<std::mutex> lock(g_queue_mutex);

            // 3. (자물쇠를 쥔 상태에서) 공유 큐에 데이터를 추가합니다.
            g_data_queue.push(i);
            std::cout << "  Produced: " << i << std::endl;
        } // Mutex is unlocked here
          // 4. lock_guard가 소멸되면서 뮤텍스가 자동으로 잠금 해제됩니다.

        // 5. 조건 변수(알림 벨)를 통해, 혹시 큐가 비어있어 잠들어 있는 소비자 스레드가 있다면
        //    '한 명만' 깨워서 "데이터가 추가되었다"고 알려줍니다.  
        g_queue_cv.notify_one(); // Notify one which is waiting consumer thread

        // 6. 100ms 동안 잠시 쉬어, 소비자가 데이터를 처리할 시간을 줍니다.
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // 7. 모든 데이터 생산이 끝났음을 알리는 단계입니다.
    // Signal that production is finished
    {
        std::lock_guard<std::mutex> lock(g_queue_mutex);
        g_finished_producing = true; // "이제 더 이상 빵 안 만듭니다" 플래그를 세웁니다.
    }

    // 8. '모든' 소비자 스레드를 깨웁니다. 큐에 데이터가 없어서 잠들어 있던 소비자들도
    //    모두 일어나서, 생산이 끝났다는 사실을 확인하고 종료할 수 있게 해줍니다.
    g_queue_cv.notify_all(); // Wake up all consumers to let them exit
}

/**
 * @brief The consumer thread: takes items from the shared queue.
 */
void consumer(int id) {
    // 1. 무한 루프를 돌며 계속해서 데이터를 처리할 준비를 합니다.
    while (true) {
        // 2. 'g_queue_mutex'를 잠급니다.
        //    std::unique_lock은 조건 변수와 함께 사용하기 위해 필요하며,
        //    수동으로 잠금을 해제하고 다시 잠글 수 있는 유연성을 제공합니다.
        std::unique_lock<std::mutex> lock(g_queue_mutex);

        // The wait function will atomically unlock the mutex and wait.
        // It waits until the lambda returns true 
        // (i.e., the queue is not empty
        //     or production is finished). 
        // When woken up, it re-locks the mutex.
        // 3. 조건 변수(알림 벨)를 기다립니다. 이 부분이 가장 중요합니다.
        //    - wait 함수는 람다 함수(predicate)의 결과가 true가 될 때까지 스레드를 재웁니다.
        //    - 스레드가 잠드는 동안, unique_lock은 '자동으로 잠금을 해제'하여 다른 스레드(생산자)가 큐에 접근할 수 있게 합니다.
        //    - notify 신호를 받아 깨어나면, '자동으로 다시 잠금을 획득'하고 람다 함수를 재평가합니다.
        //    - 조건: "큐가 비어있지 않거나" 또는 "생산이 완전히 끝났거나"
        g_queue_cv.wait(lock, [] { return !g_data_queue.empty() || g_finished_producing; });

        // 4. wait에서 깨어났을 때, 먼저 큐에 데이터가 있는지 확인합니다.
        if (!g_data_queue.empty()) {
            // 5. (자물쇠를 쥔 상태에서) 큐에서 데이터를 가져옵니다.
            int data = g_data_queue.front();
            g_data_queue.pop();

            // 6. 중요! 데이터를 처리하는 데 시간이 걸릴 수 있으므로,
            //    다른 스레드가 큐에 접근할 수 있도록 '수동으로 잠금을 먼저 해제'합니다.
            lock.unlock(); // Unlock before processing to allow other threads to work
            std::cout << "    Consumer " << id << " consumed: " << data << std::endl;
        } else if (g_finished_producing) {
            // 7. 큐는 비어있지만, 생산이 끝났다는 신호를 받았다면
            // 8. 더 이상 처리할 데이터가 없으므로 루프를 탈출하고 스레드를 종료합니다.
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

    std::thread producer_thread(producer); // 생산자 스레드 (1개): 데이터를 만들어 공유 공간(큐)에 넣는 역할 
    std::vector<std::thread> consumer_threads;
    for (int i = 0; i < 3; ++i) {        
        consumer_threads.emplace_back(consumer, i + 1); // 소비자 스레드 (3개): 공유 공간(큐)에서 데이터를 꺼내 처리하는 역할 
    }
    producer_thread.join();
    for (auto& t : consumer_threads) { t.join(); }
    std::cout << "  Producer and consumers have finished.\n";

    printLine("Multithreading Example Completed");
}