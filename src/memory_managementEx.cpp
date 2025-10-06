#include <iostream>
#include "helloEx.h" // for printLine
#include "memory_managementEx.h"

void memory_managementEx(void) {
    printLine("Demonstrating Memory Management");

    // Dynamic memory allocation using new
    int* intPtr = new int; // Allocate memory for a single integer
    *intPtr = 42;          // Assign a value
    std::cout << "Dynamically allocated integer value: " << *intPtr << std::endl;

    // Don't forget to free the allocated memory
    delete intPtr;

    // Dynamic array allocation
    int size = 5;
    int* arrPtr = new int[size]; // Allocate memory for an array of integers

    // Initialize and display the array
    for (int i = 0; i < size; i++) {
        arrPtr[i] = i * 10;
        std::cout << "arrPtr[" << i << "] = " << arrPtr[i] << std::endl;
    }

    // Free the allocated array memory
    delete[] arrPtr;

    // Demonstrating smart pointers (C++11 and later)
    {
        std::unique_ptr<int> smartIntPtr(new int(100)); // Unique ownership
        std::cout << "Smart pointer integer value: " << *smartIntPtr << std::endl;
        // No need to manually delete, will be automatically freed when going out of scope
    } // smartIntPtr goes out of scope here

    printLine("Memory Management Example Completed");

}