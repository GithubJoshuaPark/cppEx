#include <iostream>
#include "helloEx.h" // for printLine
#include "functionsEx.h"


/**
 * @brief A simple function that takes two integers and returns their sum.
 * @param a The first integer.
 * @param b The second integer.
 * @return The sum of a and b.
 */
int add(int a, int b) {
    return a + b;
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void functionsEx(void) {
    printLine("Demonstrating Functions");

    int num1 = 10;
    int num2 = 25;

    std::cout << "Before swap: num1 = " << num1 << ", num2 = " << num2 << std::endl;
    int sum = add(num1, num2);
    std::cout << "The sum of " << num1 << " and " << num2 << " is " << sum << "." << std::endl;

    swap(&num1, &num2); // Passing addresses to swap
    std::cout << "After swap: num1 = " << num1 << ", num2 = " << num2 << std::endl;
    sum = add(num1, num2);
    std::cout << "The sum of " << num1 << " and " << num2 << " is " << sum << "." << std::endl;

}