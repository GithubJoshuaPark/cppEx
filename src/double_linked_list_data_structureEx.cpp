#include <iostream>
#include "helloEx.h" // for printLine
#include "double_linked_list_data_structureEx.h"

// DNode: Structure defined in helloEx.h
// struct DNode {
//     int data;
//     struct DNode* next;
//     struct DNode* prev;
// };

// --- Doubly Linked List Operations ---

/**
 * @brief Inserts a new node at the beginning of the list.
 * @param head_ref A pointer to the head pointer of the list.
 * @param new_data The data for the new node.
 */
void insertAtBeginning(DNode** head_ref, int new_data) {
    DNode* new_node = new DNode();
    new_node->data = new_data;
    new_node->next = *head_ref;
    new_node->prev = nullptr;

    // If the list was not empty, update the prev pointer of the old head
    if (*head_ref != nullptr) {
        (*head_ref)->prev = new_node;
    }

    *head_ref = new_node;
    std::cout << "Inserted " << new_data << " at the beginning.\n";
}

/**
 * @brief Inserts a new node at the end of the list.
 * @param head_ref A pointer to the head pointer of the list.
 * @param new_data The data for the new node.
 */
void insertAtEnd(DNode** head_ref, int new_data) {
    DNode* new_node = new DNode();
    new_node->data = new_data;
    new_node->next = nullptr;

    // If the list is empty, make the new node the head
    if (*head_ref == nullptr) {
        new_node->prev = nullptr;
        *head_ref = new_node;
        std::cout << "Inserted " << new_data << " at the end (as head).\n";
        return;
    }

    // Traverse to the last node
    DNode* last = *head_ref;
    while (last->next != nullptr) {
        last = last->next;
    }

    last->next = new_node;
    new_node->prev = last;
    std::cout << "Inserted " << new_data << " at the end.\n";
}

/**
 * @brief Deletes the first node with the given key.
 * @param head_ref A pointer to the head pointer of the list.
 * @param key The data value of the node to be deleted.
 */
void deleteNode(DNode** head_ref, int key) {
    DNode* current = *head_ref;

    // Find the node to be deleted
    while (current != nullptr && current->data != key) {
        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Node with key " << key << " not found.\n";
        return;
    }

    // If the node to be deleted is the head
    if (*head_ref == current) {
        *head_ref = current->next;
    }

    // Update the 'next' pointer of the previous node
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }

    // Update the 'prev' pointer of the next node
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    delete current;
    std::cout << "Deleted node with key " << key << ".\n";
}

/**
 * @brief Prints all the elements in the linked list from head to tail.
 * @param node The head of the list.
 */
void displayListForward(DNode* node) {
    std::cout << "List (Forward):  nullptr <-> ";
    while (node != nullptr) {
        std::cout << node->data << " <-> ";
        node = node->next;
    }
    std::cout << "nullptr\n";
}

/**
 * @brief Frees all the memory used by the linked list to prevent memory leaks.
 * @param head_ref A pointer to the head pointer of the list.
 */
static void cleanupList(DNode** head_ref) {
    DNode* current = *head_ref;
    DNode* next_node = nullptr;
    while (current != nullptr) {
        next_node = current->next;
        delete current;
        current = next_node;
    }
    *head_ref = nullptr;
    std::cout << "Cleaned up all nodes in the list.\n";
}

void double_linked_list_data_structureEx(void) {
    printLine("Doubly Linked List Data Structure Example");

    DNode* head = nullptr; // Start with an empty list

    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10);
    insertAtEnd(&head, 30);
    displayListForward(head);

    deleteNode(&head, 20);
    displayListForward(head);

    deleteNode(&head, 50); // Try to delete a non-existent node
    displayListForward(head);

    // IMPORTANT: Always clean up dynamically allocated memory
    cleanupList(&head);
    displayListForward(head);

    printLine("Doubly Linked List Data Structure Example Completed");
}