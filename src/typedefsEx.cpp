#include <iostream>
#include "helloEx.h" // for printLine
#include "typedefsEx.h"

// 1. Vector2D is already defined in helloEx.h

// 2. Use 'typedef' to create a simpler alias for 'struct Vector2D'.
//    The new name 'Point' can now be used instead of 'struct Vector2D'.
typedef struct Vector2D Point;

// 3. It's also common to create an alias for simpler types to make
//    the code's intent clearer.
typedef unsigned long long ULL;

void typedefsEx(void) {
    printLine("typedefsEx function.");

    // Declare a variable the "long" way, without typedef.
    Vector2D v1 = {10.0f, 20.0f};
    std::cout << "Vector v1: (" << v1.x << ", " << v1.y << ")" << std::endl << std::endl;

    // Declare a variable the "short" way, with typedef.
    Point p1 = {30.0f, 40.0f};
    std::cout << "Point p1: (" << p1.x << ", " << p1.y << ")" << std::endl << std::endl;

    // Using the ULL typedef for an unsigned long long variable.
    ULL bigNumber = 123456789012345ULL;
    std::cout << "Big Number (ULL): " << bigNumber << std::endl;
}