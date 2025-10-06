#include <iostream>
#include "helloEx.h" // for printLine
#include "circular_linked_list_data_structureEx.h"

// Node: Structure defined in helloEx.h
// struct Node {
//     int data;
//     Node* next;
// } Node;

// --- Circular Linked List Operations ---

/**
 * @brief Inserts a new node at the beginning of the circular list.
 * @param head_ref A pointer to the head pointer of the list.
 * @param new_data The data for the new node.
 */
static void insertAtBeginning(Node** head_ref, int new_data) {
    Node* new_node = new Node();
    new_node->data = new_data;
    new_node->next = *head_ref;

    if (*head_ref == nullptr) {
        // If the list is empty, the new node points to itself.
        *head_ref = new_node;
        new_node->next = *head_ref;
    } else {
        // Traverse to the last node to update its next pointer.
        Node* last = *head_ref;
        while (last->next != *head_ref) {
            last = last->next;
        }
        last->next = new_node;
        *head_ref = new_node;
    }
    std::cout << "Inserted " << new_data << " into the circular list.\n";
}

/**
 * @brief Deletes the first node with the given key.
 * @param head_ref A pointer to the head pointer of the list.
 * @param key The data value of the node to be deleted.
 */
static void deleteNode(Node** head_ref, int key) {
    if (*head_ref == nullptr) {
        std::cout << "List is empty, cannot delete.\n";
        return;
    }

    Node* current = *head_ref;
    Node* prev = nullptr;

    // Find the node to be deleted
    do {
        if (current->data == key) {
            break;
        }
        prev = current;
        current = current->next;
    } while (current != *head_ref);

    // If node was not found
    if (current->data != key) {
        std::cout << "Node with key " << key << " not found.\n";
        return;
    }

    // If the node to be deleted is the head node
    if (current == *head_ref) {
        // Find the last node
        Node* last = *head_ref;
        while (last->next != *head_ref) {
            last = last->next;
        }
        // If it's the only node
        if (current == last) {
            *head_ref = nullptr;
        } else {
            *head_ref = current->next;
            last->next = *head_ref;
        }
    } else {
        // Unlink the node from the list
        prev->next = current->next;
    }

    delete current;
    std::cout << "Deleted node with key " << key << ".\n";
}

/**
 * @brief Prints all the elements in the circular linked list.
 * @param head The head of the list.
 */
static void displayList(Node* head) {
    if (head == nullptr) {
        std::cout << "List is empty.\n";
        return;
    }

    Node* temp = head;
    std::cout << "List: ";
    do {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != head);
    std::cout << "(head)\n";
}

/**
 * @brief Deletes the entire circular linked list to free memory.
 * @param head_ref A pointer to the head pointer of the list.
 */
static void cleanUpList(Node** head_ref) {
    if (*head_ref == nullptr) return;

    Node* current = *head_ref;
    Node* next_node;

    // Break the circular link to avoid infinite loop
    Node* last = *head_ref;
    while (last->next != *head_ref) {
        last = last->next;
    }
    last->next = nullptr; // Break the circular link

    while (current != nullptr) {
        next_node = current->next;
        delete current;
        current = next_node;
    }

    *head_ref = nullptr; // Finally, set head to nullptr
}

void circular_linked_list_data_structureEx(void) {
    printLine("Circular Linked List Data Structure Example");

    Node* head = nullptr;

    insertAtBeginning(&head, 30);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10);
    displayList(head);

    deleteNode(&head, 20);
    displayList(head);

    deleteNode(&head, 10); // Deleting the head
    displayList(head);

    deleteNode(&head, 30); // Deleting the last node
    displayList(head);

    cleanUpList(&head); // Clean up the list

    printLine("Circular Linked List Data Structure Example Completed");
}