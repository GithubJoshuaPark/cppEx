#include <iostream>
#include <string>
#include <vector>
#include <list>      // Using std::list for chaining
#include "helloEx.h" // for printLine
#include "hash_table_data_structureEx.h"

const int TABLE_SIZE = 10;

// A node in the hash table chain
struct HashNode {
    std::string key;
    int value;
};

class HashTable {
private:
    // table is a vector of lists. Each list is a chain for a bucket.
    std::vector<std::list<HashNode>> table;

    /**
     * @brief A simple hash function that sums the ASCII values of characters.
     * @param key The string key to hash.
     * @return An index for the hash table.
     */
    int hashFunction(const std::string& key) {
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % TABLE_SIZE;
    }

public:
    /**
     * @brief Constructor to initialize the table size.
     */
    HashTable() : table(TABLE_SIZE) {}

    /**
     * @brief Inserts a key-value pair into the hash table.
     * If the key already exists, its value is updated.
     */
    void insert(const std::string& key, int value) {
        int index = hashFunction(key);
        // Find if the key already exists in the chain
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value; // Update existing key
                std::cout << "Updated key '" << key << "' with value " << value << ".\n";
                return;
            }
        }
        // If key not found, add a new node to the chain
        table[index].push_back({key, value});
        std::cout << "Inserted key '" << key << "' with value " << value << " at index " << index << ".\n";
    }

    /**
     * @brief Searches for a key and returns its value.
     * @return The value if the key is found, otherwise -1.
     */
    int search(const std::string& key) {
        int index = hashFunction(key);
        for (const auto& node : table[index]) {
            if (node.key == key) {
                std::cout << "Found key '" << key << "', value is " << node.value << ".\n";
                return node.value;
            }
        }
        std::cout << "Key '" << key << "' not found.\n";
        return -1; // Not found
    }

    /**
     * @brief Removes a key-value pair from the hash table.
     */
    void remove(const std::string& key) {
        int index = hashFunction(key);
        table[index].remove_if([&](const HashNode& node) {
            if (node.key == key) {
                std::cout << "Removed key '" << key << "'.\n";
                return true;
            }
            return false;
        });
    }

    /**
     * @brief Displays the contents of the hash table.
     */
    void display() {
        printLine("Hash Table Contents");
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& node : table[i]) {
                std::cout << "['" << node.key << "':" << node.value << "] -> ";
            }
            std::cout << "nullptr\n";
        }
    }
};

void hash_table_data_structureEx(void) {
    printLine("Hash Table Data Structure Example");

    HashTable ht;

    ht.insert("apple", 10);
    ht.insert("banana", 20);
    ht.insert("orange", 30);
    ht.insert("grape", 40); // This might collide with "apple"
    ht.insert("melon", 50);
    std::cout << std::endl;

    ht.display();
    std::cout << std::endl;

    ht.search("orange");
    ht.search("grape");
    ht.search("watermelon");
    std::cout << std::endl;

    ht.remove("banana");
    ht.display();
}