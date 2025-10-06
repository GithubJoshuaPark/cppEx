#include <iostream>
#include "helloEx.h" // for printLine
#include "stack_data_structureEx.h"

// Node: Structure defined in helloEx.h 

void stack_data_structureEx(void) {
    printLine("Demonstrating Stack Data Structure");
    Node* top = nullptr; // Initialize the top of the stack to nullptr

    // Push function to add an element to the stack
    auto push = [&](int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
        std::cout << "Pushed " << value << " onto the stack.\n";
    };

    // Pop function to remove and return the top element of the stack
    auto pop = [&]() -> int {
        if (top == nullptr) {
            std::cerr << "Stack underflow! Cannot pop from an empty stack.\n";
            return -1; // Indicate an error
        }
        int poppedValue = top->data;
        Node* temp = top;
        top = top->next;
        delete temp; // Free the memory
        std::cout << "Popped " << poppedValue << " from the stack.\n";
        return poppedValue;
    };

    // Peek function to view the top element without removing it
    auto peek = [&]() -> int {
        if (top == nullptr) {
            std::cerr << "Stack is empty! Cannot peek.\n";
            return -1; // Indicate an error
        }
        return top->data;
    };
    // Check if the stack is empty
    auto isEmpty = [&]() -> bool {
        return top == nullptr;
    };

    // Test the stack operations
    push(10);
    push(20);
    push(30);   
    std::cout << "Top element is: " << peek() << std::endl;
    pop();
    std::cout << "Top element after pop is: " << peek() << std::endl;
    pop();
    pop();
    pop(); // Attempt to pop from an empty stack        
    std::cout << "Is stack empty? " << (isEmpty() ? "Yes" : "No") << std::endl;
    
    printLine("Stack Data Structure Example Completed");
}