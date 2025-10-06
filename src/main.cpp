#include <iostream>
#include <vector>
#include <limits>   // Required for numeric_limits
#include "helloEx.h" // Note: This file uses C-style printf
#include "vectorEx.h"
#include "data_typesEx.h"
#include "functionsEx.h"
#include "pointersEx.h"
#include "arraysEx.h"
#include "structuresEx.h"
#include "unionsEx.h" // For the unions example
#include "enumsEx.h"  // For the enums example
#include "typedefsEx.h" // For the typedefs example
#include "taskManagementEx.h" // For the task management example
#include "memory_managementEx.h" // For the memory management example
#include "dynamic_memory_allocationEx.h" // For the dynamic memory allocation example
#include "file_ioEx.h"
#include "stack_data_structureEx.h"
#include "queue_data_structureEx.h"
#include "linked_list_data_structureEx.h"
#include "double_linked_list_data_structureEx.h"
#include "circular_linked_list_data_structureEx.h"
#include "binary_tree_data_structureEx.h"
#include "searching_algorithmsEx.h"
#include "sorting_algorithmsEx.h"
#include "bit_manipulationEx.h"
#include "preprocessor_directivesEx.h"
#include "error_handlingEx.h"

// To build and run this project in VSCode on macOS,
//    press Cmd+Shift+B to build, 
// or press F5          to build+debug.

// or build and run from the terminal:
//    $ make        # build the project
//    $ ./bin/main  # run the main executable

// --- Type Definitions for a Data-Driven Menu ---

/**
 * @brief A function pointer type for our example functions.
 * All example functions must match this signature (take no arguments, return void).
 */
typedef void (*ExampleFunc)(void);

/**
 * @brief A structure to hold the information for a single menu item.
 */
typedef struct MenuItem{
    const char* description; // The text to display in the menu
    ExampleFunc function;    // A pointer to the function to execute
} MenuItem;

// --- Menu Definition ---

// This array now drives the entire menu and dispatch logic.
// To add a new item, just add a new line here.
MenuItem menu_items[] = {
    {"Hello World", say_hello},                                           // Example function from helloEx.c
    {"Data Types Example", data_typesEx},                                 // Example function from data_typesEx.cpp
    {"Functions Example", functionsEx},                                   // Example function from functionsEx.cpp
    {"Pointers Example", pointersEx},                                     // Example function from pointersEx.cpp
    {"Arrays Example", arraysEx},                                         // Example function from arraysEx.cpp
    {"Vector Example", vectorEx},                                         // Example function from vectorEx.cpp
    {"Structures Example", structuresEx},                                 // Example function from structuresEx.cpp
    {"Unions Example", unionsEx},                                         // Example function from unionsEx.cpp
    {"Enums Example", enumsEx},                                           // Example function from enumsEx.cpp
    {"Typedefs Example", typedefsEx},                                     // Example function from typedefsEx.cpp
    {"Task Management Example", taskManagementEx},                        // Example function from taskManagementEx.cpp
    {"Memory Management Example", memory_managementEx},                   // Example function from memory_managementEx.cpp
    {"Dynamic Memory Allocation Example", dynamic_memory_allocationEx},   // Example function from dynamic_memory_allocationEx.cpp
    {"File I/O Example", file_ioEx},                                      // Example function from file_ioEx.cpp
    {"Stack Data Structure Example", stack_data_structureEx},             // Example function from stack_data_structureEx.cpp
    {"Queue Data Structure Example", queue_data_structureEx},             // Example function from queue_data_structureEx.cpp
    {"Linked List Data Structure Example", linked_list_data_structureEx}, // Example function from linked_list_data_structureEx.cpp
    {"Double Linked List Example", double_linked_list_data_structureEx},  // Example function from double_linked_list_data_structureEx.cpp
    {"Circular Linked List Example", circular_linked_list_data_structureEx}, // Example function from circular_linked_list_data_structureEx.cpp
    {"Binary Tree Example", binary_tree_data_structureEx},                // Example function from binary_tree_data_structureEx.cpp
    {"Searching Algorithms Example", searching_algorithmsEx},             // Example function from searching_algorithmsEx.cpp
    {"Sorting Algorithms Example", sorting_algorithmsEx},                 // Example function from sorting_algorithmsEx.cpp
    {"Bit Manipulation Example", bit_manipulationEx},                     // Example function from bit_manipulationEx.cpp
    {"Preprocessor Directives Example", preprocessor_directivesEx},       // Example function from preprocessor_directivesEx.cpp
    {"Error Handling Example", error_handlingEx},                         // Example function from error_handlingEx.cpp
};

// Calculate the number of items in the menu array.
const int num_menu_items = sizeof(menu_items) / sizeof(menu_items[0]);

// --- Utility Functions ---

void clear_input_buffer(void) {
    // Clear the error flags and discard characters until a newline is found.
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clear_screen(void) {
    // system("clear") is fine, but for pure C++ this avoids a shell call.
    // This is a simple alternative for demonstration.
    std::cout << "\033[2J\033[1;1H";
}

void show_menu(void) {
    printLine("C++ Language Interactive Examples");
    for (int i = 0; i < num_menu_items; i++) {
        std::cout << " " << (i + 1) << ". " << menu_items[i].description << std::endl;
    }
    std::cout << " 99. Exit" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

/**
 * @brief The main function that drives the menu system.
 */
int main() {

    int choice = 0;

    while (choice != 99) {
        clear_screen();
        show_menu();
        std::cout << "Enter your choice: ";

        // Use C++ style input with error checking
        if (!(std::cin >> choice)) {
            std::cout << "\nInvalid input. Please enter a number.\n";
            clear_input_buffer();
            std::cout << "Press Enter to continue...";
            std::cin.get(); // Wait for user to press Enter
            continue;
        }
        clear_input_buffer(); // Clear the rest of the line (e.g., the newline character)

        if (choice == 99) {
            printf("\nExiting the program.\n");
            break;
        }

        // The choice is 1-based, our array is 0-based.
        int index = choice - 1;

        if (index >= 0 && index < num_menu_items) {
            clear_screen();
            // Execute the function using the function pointer from the array
            menu_items[index].function();
            std::cout << "\nPress Enter to return to the menu...";
            std::cin.get(); // Wait for user to press Enter
        } else {
            std::cout << "\nInvalid choice. Please try again.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get(); // Wait for user to press Enter
        }
    }
    return 0;
}