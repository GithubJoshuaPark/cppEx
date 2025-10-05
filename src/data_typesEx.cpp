#include <iostream>
#include "helloEx.h" // for printLine
#include "data_typesEx.h"

void data_typesEx(void) {
    printLine("data_typesEx function.");
    
    // Integer type: for whole numbers
    int age = 30;

    // Floating-point type: for numbers with a decimal point
    float weight = 155.5f; // 'f' suffix is good practice for float literals

    // Double-precision floating-point type: for more precise decimal numbers
    double pi = 3.14159265359;

    // Character type: for single characters
    char initial = 'J';
    char name[] = "John Doe"; // String as a character array

    // Boolean type: for true/false values
    bool is_student = false;

    // std:cout to display the values
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Weight: " << weight << " lbs" << std::endl;
    std::cout << "Pi: " << pi << std::endl;
    std::cout << "Initial: " << initial << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Is Student: " << (is_student ? "Yes" : "No") << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    // Display sizes of each data type
    std::cout << "Size of int: " << sizeof(age) << " bytes" << std::endl;
    std::cout << "Size of float: " << sizeof(weight) << " bytes" << std::endl;
    std::cout << "Size of double: " << sizeof(pi) << " bytes" << std::endl;
    std::cout << "Size of char: " << sizeof(initial) << " bytes" << std::endl;
    std::cout << "Size of bool: " << sizeof(is_student) << " bytes" << std::endl;
}