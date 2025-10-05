#include <iostream>
#include "helloEx.h" // Note: This file uses C-style printf
#include "pointersEx.h"

void pointersEx(void) {
    printLine("Demonstrating Pointers");

    int value = 42;          // An integer variable
    int* ptr = &value;      // A pointer variable that holds the address of 'value'

    int array[][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Print the value and its address
    std::cout << "Value: " << value << std::endl;
    std::cout << "Address of value: " << &value << std::endl;

    // Print the pointer and the value it points to
    std::cout << "Pointer ptr: " << ptr << std::endl;
    std::cout << "Value pointed to by ptr: " << *ptr << std::endl;

    // Modify the value using the pointer
    *ptr = 100;
    std::cout << "New Value after modifying through pointer: " << value << std::endl;

    // Demonstrate pointer arithmetic with a 2D array
    std::cout << "Accessing 2D array elements using pointer arithmetic:" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Calculate the address of array[i][j] using pointer arithmetic
            int* elementPtr = *(array + i) + j;
            std::cout << "Element at (" << i << "," << j << "): " << *elementPtr 
                      << " at address: " << elementPtr
                      << std::endl;
        }
    }

}