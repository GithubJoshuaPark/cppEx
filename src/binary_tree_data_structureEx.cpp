#include <iostream>
#include "helloEx.h" // for printLine
#include <limits>    // For std::numeric_limits
#include "binary_tree_data_structureEx.h"

// TreeNode structure defined in helloEx.h
// struct TreeNode {
//     int data;
//     struct TreeNode* left;
//     struct TreeNode* right;
// };

// --- Binary Tree Operations ---

/**
 * @brief Creates a new tree node.
 * @param data The data for the new node.
 * @return A pointer to the newly created node.
 */
TreeNode* createNode(int data) {
    TreeNode* newNode = new TreeNode();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

/**
 * @brief Inserts a new node into a Binary Search Tree (BST).
 * @param root The root of the tree/subtree to insert into.
 * @param data The data for the new node.
 * @return The root of the modified tree.
 */
TreeNode* insertNode(TreeNode* root, int data) {
    // If the tree is empty, return a new node.
    if (root == nullptr) {
        return createNode(data);
    }

    // Otherwise, recur down the tree.
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }

    return root;
}

/**
 * @brief Performs an in-order traversal (Left, Root, Right).
 * For a BST, this will print the elements in sorted order.
 */
void inorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        std::cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

/**
 * @brief Performs a pre-order traversal (Root, Left, Right).
 */
void preorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        std::cout << root->data << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

/**
 * @brief Performs a post-order traversal (Left, Right, Root).
 * This is useful for deleting a tree.
 */
void postorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        std::cout << root->data << " ";
    }
}

/**
 * @brief Finds the node with the minimum value in a given tree.
 * In a BST, this is the leftmost node.
 * @param node The root of the tree to search in.
 * @return A pointer to the node with the minimum value.
 */
TreeNode* findMinValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

/**
 * @brief Deletes a node with the given key from the Binary Search Tree (BST).
 * @param root The root of the tree/subtree to delete from.
 * @param key The data of the node to delete.
 * @return The root of the modified tree.
 */
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) {
        std::cout << "\nNode with key " << key << " not found.\n";
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else { // Node with the key is found
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        TreeNode* temp = findMinValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

/**
 * @brief Deletes the entire tree to free memory.
 */
void cleanupTree(TreeNode* root) {
    if (root != nullptr) {
        cleanupTree(root->left);
        cleanupTree(root->right);
        delete root;
    }
}

/**
 * @brief A utility function to print a 2D representation of the binary tree.
 * It performs a reverse in-order traversal.
 * @param root The root of the tree/subtree to print.
 * @param space The current indentation space.
 */
void print2DTreeUtil(TreeNode* root, int space) {
    const int COUNT = 10;

    // Base case
    if (root == nullptr) {
        return;
    }

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DTreeUtil(root->right, space);

    // Print current node after space
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++) {
        std::cout << " ";
    }
    std::cout << root->data << "\n";

    // Process left child
    print2DTreeUtil(root->left, space);
}

/**
 * @brief Displays a menu for tree traversal options and executes the chosen one.
 * @param root The root of the tree to traverse.
 */
void TreeMenuShow(TreeNode*& root) { // Pass root by reference to allow modification
    int choice = 0;
    while (choice != 7) {
        printLine("Binary Tree Menu");
        std::cout << "1. In-order Traversal (sorted)\n";
        std::cout << "2. Pre-order Traversal\n";
        std::cout << "3. Post-order Traversal\n";
        std::cout << "4. Insert Node\n";
        std::cout << "5. Delete Node\n";
        std::cout << "6. Print 2D Tree\n";
        std::cout << "7. Back to main menu\n";
        std::cout << "--------------------------------\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\nInvalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: std::cout << "\nIn-order: "; inorderTraversal(root); std::cout << "\n\n"; break;
            case 2: std::cout << "\nPre-order: "; preorderTraversal(root); std::cout << "\n\n"; break;
            case 3: std::cout << "\nPost-order: "; postorderTraversal(root); std::cout << "\n\n"; break;
            case 4: {
                int number_to_insert;
                std::cout << "Enter number to insert: ";
                std::cin >> number_to_insert;
                if (!std::cin.fail()) {
                    root = insertNode(root, number_to_insert);
                    std::cout << "Node " << number_to_insert << " inserted.\n\n";
                } else {
                    std::cout << "Invalid input.\n";
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            case 5: {
                int number_to_delete;
                std::cout << "Enter number to delete: ";
                std::cin >> number_to_delete;
                root = deleteNode(root, number_to_delete);
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            case 6: {
                std::cout << "\n--- 2D Tree Representation ---\n";
                print2DTreeUtil(root, 0);
                std::cout << "\n------------------------------\n\n";
                break;
            }
            case 7: break;
            default: std::cout << "\nInvalid choice. Please try again.\n\n"; break;
        }
    }
}

void binary_tree_data_structureEx(void) {
    printLine("Binary Tree Data Structure Example");

    TreeNode* root = nullptr; // Start with an empty tree
    
    // Initial nodes for demonstration
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 70);

    // Show the traversal menu
    TreeMenuShow(root);

    // IMPORTANT: Clean up all dynamically allocated nodes
    cleanupTree(root);
    root = nullptr; // Good practice to nullify pointer after cleanup
    std::cout << "\nTree has been cleaned up." << std::endl;

    printLine("Binary Tree Data Structure Example Completed");
}