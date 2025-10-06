#include <iostream>
#include <memory> // Required for smart pointers (unique_ptr, shared_ptr)
#include <vector>
#include "helloEx.h" // for printLine
#include "dynamic_memory_allocationEx.h"

void dynamic_memory_allocationEx(void) {
    printLine("Demonstrating Dynamic Memory Allocation");

    // --- 1. Manual Memory Management (The C-style way) ---
    std::cout << "--- 1. Manual Memory Management with new/delete ---\n";
    // Allocate memory for a single integer on the heap
    int* intPtr = new int; 
    *intPtr = 42;
    std::cout << "Dynamically allocated integer value: " << *intPtr << " at address " << intPtr << std::endl;

    // IMPORTANT: You must manually free the allocated memory to prevent a memory leak.
    delete intPtr;
    intPtr = nullptr; // Good practice to nullify pointer after deletion
    std::cout << "Memory for single integer has been freed.\n\n";

    // Allocate memory for an array of integers on the heap
    int size = 5;
    int* arrPtr = new int[size];
    std::cout << "Dynamically allocated array at address " << arrPtr << std::endl;

    for (int i = 0; i < size; ++i) {
        arrPtr[i] = (i + 1) * 10;
        std::cout << "arrPtr[" << i << "] = " << arrPtr[i] << std::endl;
    }

    // IMPORTANT: For arrays, you must use delete[] to free the memory.
    delete[] arrPtr;
    arrPtr = nullptr;
    std::cout << "Memory for array has been freed.\n\n";

    // --- 2. Modern C++: Smart Pointers (RAII - Resource Acquisition Is Initialization) ---
    std::cout << "--- 2. Modern C++ with Smart Pointers ---\n";
    
    // a) std::unique_ptr: Exclusive ownership. Memory is automatically freed when the pointer goes out of scope.
    {
        std::cout << "Entering unique_ptr scope...\n";
        // Use std::make_unique for safer, more efficient allocation
        std::unique_ptr<int> smartIntPtr = std::make_unique<int>(100);
        std::cout << "unique_ptr value: " << *smartIntPtr << std::endl;
        // No 'delete' needed!
    } // smartIntPtr goes out of scope here, and the memory is automatically freed.
    std::cout << "unique_ptr has gone out of scope and freed its memory.\n\n";

    // b) std::shared_ptr: Shared ownership. Memory is freed only when the last shared_ptr pointing to it is destroyed.
    std::shared_ptr<int> sharedPtr1;
    {
        std::cout << "Entering shared_ptr scope...\n";
        // Create one shared_ptr
        sharedPtr1 = std::make_shared<int>(200);
        // Create a second shared_ptr that shares ownership of the same memory
        std::shared_ptr<int> sharedPtr2 = sharedPtr1;

        std::cout << "shared_ptr value: " << *sharedPtr1 << std::endl;
        std::cout << "Ownership count: " << sharedPtr1.use_count() << " (shared by sharedPtr1 and sharedPtr2)\n";
    } // sharedPtr2 goes out of scope, but memory is NOT freed yet (count is still 1).
    std::cout << "shared_ptr scope has ended. Ownership count: " << sharedPtr1.use_count() << std::endl;
    // The memory for 200 is finally freed when sharedPtr1 is destroyed at the end of this function.

    printLine("Dynamic Memory Allocation Example Completed");
}
