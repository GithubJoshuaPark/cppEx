#include <iostream>
#include <vector>
#include <algorithm> // For std::swap
#include <limits>    // For std::numeric_limits
#include "helloEx.h" // for printLine
#include "sorting_algorithmsEx.h"

void printSortVector(const std::string& title, const std::vector<int>& arr) {
    std::cout << title;
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// --- Sorting Algorithm Implementations ---

// 1. Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    size_t n = arr.size();
    bool swapped;
    for (size_t i = 0; i < n - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// 2. Selection Sort
void selectionSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[min_idx], arr[i]);
        }
    }
}

// 3. Quick Sort (Lomuto partition scheme)
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}


void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 4. Quick Sort (Hoare partition scheme variant)
void quickSortHoare(std::vector<int>& arr, int low, int high) {
    if (low >= high) {
        return;
    }

    int i = low;
    int j = high;
    int pivot = arr[low]; // Using the first element as the pivot

    while (i < j) {
        while (i < j && arr[j] >= pivot) { j--; }
        while (i < j && arr[i] <= pivot) { i++; }
        if (i < j) {
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[low], arr[i]); // Place pivot in its final sorted position
    quickSortHoare(arr, low, i - 1);
    quickSortHoare(arr, i + 1, high);
}

void sorting_algorithmsEx(void) {
    printLine("Sorting Algorithms Example");

    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90, 5};
    int choice = 0;

    while (choice != 5) {
        std::cout << "\n--- Sort Menu ---\n";
        printSortVector("Original Data: ", data);

        std::cout << "\n1. Bubble Sort\n";
        std::cout << "2. Selection Sort\n";
        std::cout << "3. Quick Sort (Lomuto)\n";
        std::cout << "4. Quick Sort (Hoare)\n";
        std::cout << "5. Back to main menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 5) {
            std::cout << "\nInvalid input. Please enter a number between 1 and 5.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 5) break;

        std::vector<int> sorted_data = data;
        if (choice == 1) {
            bubbleSort(sorted_data);
            printSortVector("Bubble Sorted: ", sorted_data);
        } else if (choice == 2) {
            selectionSort(sorted_data);
            printSortVector("Selection Sorted: ", sorted_data);
        } else if (choice == 3) {
            quickSort(sorted_data, 0, static_cast<int>(sorted_data.size() - 1));
            printSortVector("Quick Sorted (Lomuto): ", sorted_data);
        } else if (choice == 4) {
            quickSortHoare(sorted_data, 0, static_cast<int>(sorted_data.size() - 1));
            printSortVector("Quick Sorted (Hoare): ", sorted_data);
        }
    }
}