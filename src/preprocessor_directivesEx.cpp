#include <iostream>
#include "helloEx.h" // for printLine
#include "preprocessor_directivesEx.h"

// 1. #define: Defines a macro. The preprocessor will replace every occurrence
//    of PI with 3.14159 before the compiler sees the code.
#define PI 3.14159

// 2. Function-like macro: Replaces SQUARE(x) with ((x) * (x)).
//    Parentheses are crucial to avoid operator precedence issues.
#define SQUARE(x) ((x) * (x))

// 3. Conditional compilation: We can define a symbol to control which
//    code blocks are included in the final compilation.
//    Try commenting out the line below and re-compiling to see the difference.
#define DEBUG_MODE

void preprocessor_directivesEx(void) {
    printLine("Preprocessor Directives Example");

    // Using the PI macro
    double radius = 5.0;
    double area = PI * SQUARE(radius);
    std::cout << "The area of a circle with radius " << radius << " is: " << area << std::endl;

    // Using the SQUARE macro
    int num = 7;
    std::cout << "The square of " << num << " is: " << SQUARE(num) << std::endl;

    std::cout << "\n--- Conditional Compilation ---\n";

    // 4. #ifdef, #else, #endif: These directives check if a macro is defined.
    //    If DEBUG_MODE is defined, the first block is compiled.
    //    Otherwise, the #else block is compiled.
#ifdef DEBUG_MODE
    std::cout << "Debug mode is ON." << std::endl;
    std::cout << "This message is only visible during debugging." << std::endl;
#else
    std::cout << "Debug mode is OFF." << std::endl;
    std::cout << "This is the release version." << std::endl;
#endif

    // 5. Predefined macros
    std::cout << "\n--- Predefined Macros ---\n";
    std::cout << "This code was compiled on: " << __DATE__ << " at " << __TIME__ << std::endl;
    std::cout << "File: " << __FILE__ << ", Line: " << __LINE__ << std::endl;
}