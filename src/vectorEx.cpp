#include <iostream>
#include "helloEx.h"  // For printLine
#include "vectorEx.h"


void vectorEx(void) {
    printLine("vectorEx function.");

    std::vector<int> v{1,2,3,4};
    std::cout << "Hello from C++ on macOS (clang)\n";

    for (int x : v) {
        std::cout << x << ' ';
    }    
    std::cout << '\n';
}