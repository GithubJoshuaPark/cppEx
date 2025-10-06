#include <iostream>
#include "helloEx.h" // for printLine
#include "linked_list_data_structureEx.h"

// Node: Structure defined in helloEx.h
// struct Node {
//     int data;
//     Node* next;
// };

// --- Linked List Operations ---

/**
 * @brief Inserts a new node at the beginning of the list.
 * @param head_ref A pointer to the head pointer of the list.
 * @param new_data The data for the new node.
 */
static void insertAtBeginning(Node** head_ref, int new_data) {
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
    std::cout << "Inserted " << new_data << " at the beginning.\n";
}

/**
 * @brief Deletes the first node with the given key.
 * @param head_ref A pointer to the head pointer of the list.
 * @param key The data value of the node to be deleted.
 */
static void deleteNode(Node** head_ref, int key) {
    Node* temp = *head_ref;
    Node* prev = nullptr;

    // If head node itself holds the key to be deleted
    if (temp != nullptr && temp->data == key) {
        *head_ref = temp->next; // Changed head
        delete temp;            // free old head
        std::cout << "Deleted node with key " << key << ".\n";
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != nullptr && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == nullptr) {
        std::cout << "Node with key " << key << " not found.\n";
        return;
    }

    // Unlink the node from linked list
    prev->next = temp->next;
    delete temp; // Free memory
    std::cout << "Deleted node with key " << key << ".\n";
}

/**
 * @brief Prints all the elements in the linked list.
 * @param node The head of the list.
 */
static void displayList(Node* node) {
    std::cout << "List: ";
    while (node != nullptr) {
        std::cout << node->data << " -> ";
        node = node->next;
    }
    std::cout << "nullptr\n";
}

/**
 * @brief Frees all the memory used by the linked list to prevent memory leaks.
 * @param head_ref A pointer to the head pointer of the list.
 */
static void cleanupList(Node** head_ref) {
    Node* current = *head_ref;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    *head_ref = nullptr; // Set head to null after cleanup
    std::cout << "Cleaned up all nodes in the list.\n";
}

void linked_list_data_structureEx(void) {
    printLine("Linked List Data Structure Example");

    Node* head = nullptr; // Start with an empty list

    // Test the operations
    insertAtBeginning(&head, 30);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10);
    displayList(head);

    deleteNode(&head, 20);
    displayList(head);

    deleteNode(&head, 50); // Try to delete a non-existent node
    displayList(head);

    // IMPORTANT: Always clean up dynamically allocated memory
    cleanupList(&head);
    displayList(head);

    printLine("Linked List Data Structure Example Completed");
}