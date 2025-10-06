#include <iostream>
#include "helloEx.h" // For printLine
#include "arraysEx.h"

void arraysEx(void) {
    printLine("Demonstrating Arrays");

    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    std::cout << "Array elements: ";
    std::cout << "The memory address of the start of the array is: " << numbers << std::endl;
    std::cout << "The memory address of the first element is: " << &numbers [0] << std::endl;
    std::cout << "The memory address of the second element is: " << &numbers [1] << std::endl;
    std::cout << "The memory address of the third element is: " << &numbers [2] << std::endl;
    std::cout << "The memory address of the fourth element is: " << &numbers [3] << std::endl;
    std::cout << "The memory address of the fifth element is: " << &numbers [4] << std::endl;   

    for(int i = 0; i < size; i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
}