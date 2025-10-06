#include <iostream>
#include <stdexcept> // For std::runtime_error
#include "helloEx.h" // for printLine
#include "error_handlingEx.h"

/**
 * @brief A simple class demonstrating the RAII (Resource Acquisition Is Initialization) principle.
 * The destructor is automatically called when the object goes out of scope,
 * ensuring cleanup happens, much like a 'finally' block in other languages.
 */
class ResourceGuard {
public:
    ResourceGuard(const std::string& name) : resource_name(name) {
        std::cout << "  [RAII] Acquiring resource: " << resource_name << std::endl;
    }

    ~ResourceGuard() {
        std::cout << "  [RAII] Releasing resource: " << resource_name << ". Cleanup is guaranteed!" << std::endl;
    }

private:
    std::string resource_name;
};

/**
 * @brief A function that might throw an exception.
 * @param a The numerator.
 * @param b The denominator.
 * @return The result of a / b.
 * @throws std::runtime_error if b is zero.
 */
double divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero condition!");
    }
    return static_cast<double>(a) / b;
}

void error_handlingEx(void) {
    printLine("Error Handling Example (try, catch, and RAII)");

    // --- Scenario 1: Successful execution ---
    std::cout << "--- Scenario 1: No error ---\n";
    try {
        ResourceGuard guard1("File Handle"); // Resource is acquired here.
        std::cout << "  Attempting to divide 10 by 2...\n";
        double result = divide(10, 2);
        std::cout << "  Result: " << result << std::endl;
    } // guard1 goes out of scope here, destructor is called automatically.
    catch (const std::exception& e) {
        std::cerr << "  Caught an exception: " << e.what() << '\n';
    }

    std::cout << "\n--- Scenario 2: Error occurs ---\n";
    // --- Scenario 2: An exception is thrown ---
    try {
        ResourceGuard guard2("Network Connection"); // Resource is acquired here.
        std::cout << "  Attempting to divide 10 by 0...\n";
        double result = divide(10, 0);
        // This line will not be reached.
        std::cout << "  Result: " << result << std::endl;
    } // An exception is thrown. Before the catch block is executed,
      // the stack is "unwound", and guard2's destructor is called automatically.
    catch (const std::runtime_error& e) {
        std::cerr << "  Caught a runtime_error: " << e.what() << '\n';
    } catch (const std::exception& e) {
        // This is a fallback for other standard exceptions.
        std::cerr << "  Caught a general exception: " << e.what() << '\n';
    }
}