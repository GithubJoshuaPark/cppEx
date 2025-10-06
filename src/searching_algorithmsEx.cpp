#include <iostream>
#include <vector>
#include <algorithm> // For std::sort
#include <limits>    // For std::numeric_limits
#include "helloEx.h" // for printLine
#include "searching_algorithmsEx.h"

/**
 * @brief Performs a linear search on a vector.
 * It iterates through each element sequentially.
 * @param arr The vector to search in.
 * @param target The value to search for.
 * @return The index of the target if found, otherwise -1.
 */
int linearSearch(const std::vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return static_cast<int>(i); // Found
        }
    }
    return -1; // Not found
}

/**
 * @brief Performs a binary search on a sorted vector.
 * It repeatedly divides the search interval in half.
 * @param arr The sorted vector to search in.
 * @param target The value to search for.
 * @return The index of the target if found, otherwise -1.
 */
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // Avoid potential overflow

        if (arr[mid] == target) {
            return mid; // Found
        }

        if (arr[mid] < target) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }

    return -1; // Not found
}

/**
 * @brief Prints the elements of a vector.
 */
void printVector(const std::vector<int>& arr) {
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void searching_algorithmsEx(void) {
    printLine("Searching Algorithms Example");

    std::vector<int> data = {27, 10, 88, 1, 65, 34, 9, 52, 17};
    int target;
    int choice = 0;

    while (choice != 3) {
        std::cout << "\n--- Search Menu ---\n";
        std::cout << "Unsorted Data: ";
        printVector(data);
        
        // Binary search requires sorted data
        std::vector<int> sorted_data = data;
        std::sort(sorted_data.begin(), sorted_data.end());
        std::cout << "Sorted Data  : ";
        printVector(sorted_data);

        std::cout << "\n1. Linear Search (on unsorted data)\n";
        std::cout << "2. Binary Search (on sorted data)\n";
        std::cout << "3. Back to main menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 3) {
            std::cout << "\nInvalid input. Please enter a number between 1 and 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 3) break;

        std::cout << "Enter the number to search for: ";
        std::cin >> target;

        int result = (choice == 1) ? linearSearch(data, target) : binarySearch(sorted_data, target);

        if (result != -1) {
            std::cout << "-> Found " << target << " at index " << result << ".\n";
        } else {
            std::cout << "-> " << target << " was not found.\n";
        }
    }
}
