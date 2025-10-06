#include <iostream>
#include "helloEx.h" // for printLine
#include "unionsEx.h"

// 1. Data, a union type is already defined in helloEx.h

void unionsEx(void) {
    printLine("Demonstrating Unions");

    // 2. Declare a variable of our new 'union Data' type.
    Data data;  

    std::cout << "Memory size of union Data: " << sizeof(data) << " bytes" 
              << "(size of largest member, char[20])" << std::endl << std::endl;

    // 3. Assign and access the union members.
    data.i = 10;
    std::cout << "Data after assigning an integer value:" << std::endl;
    std::cout << "Data.i: " << data.i << std::endl<< std::endl;

    data.f = 220.5f;
    std::cout << "Data after assigning a float value:" << std::endl;
    std::cout << "Data.f: " << data.f << std::endl << std::endl;

    strcpy(data.str, "C++ Programming");
    std::cout << "Data after assigning a string value:" << std::endl;
    std::cout << "Data.str: " << data.str << std::endl << std::endl;

    std::cout << "Note: Assigning to one member of the union overwrites the others." << std::endl;
    
}