#include <iostream>
#include <vector> // vector is part of the C++ Standard Library
#include <algorithm> // for std::find
#include "helloEx.h"  // For printLine
#include "vectorEx.h"

/**
 * @brief Prints all elements in a vector.
 * @param vec A const reference to the vector to be printed.
 * Passing by const reference is efficient and safe for read-only operations.
 */
void printVector(const std::string& title, const std::vector<int>& vec) {
    std::cout << title;
    for (int x : vec) {
        std::cout << x << ' ';
    }
    std::cout << "| size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
}

/**
 * Entry point for the vector example.
 * Demonstrates commonly used member functions of std::vector.
 */
void vectorEx(void) {
    printLine("vectorEx function.");

    // 1. 생성 및 요소 추가 (Creation and Modifiers)
    std::vector<int> v;
    printVector("Initial empty vector: ", v);

    std::cout << "\n--- Adding elements ---\n";
    v.push_back(10); // 가장 기본적인 추가 방법
    v.push_back(20);
    v.emplace_back(30); // push_back 보다 효율적일 수 있음
    printVector("After push_back/emplace_back: ", v);

    // 2. 요소 접근 (Element Access)
    std::cout << "\n--- Accessing elements ---\n";
    std::cout << "First element using front(): " << v.front() << std::endl;
    std::cout << "Last element using back(): " << v.back() << std::endl;
    std::cout << "Element at index 1 using []: " << v[1] << std::endl;
    std::cout << "Element at index 1 using at(): " << v.at(1) << std::endl;

    // 3. 반복자와 삽입/삭제 (Iterators and insert/erase)
    std::cout << "\n--- Inserting and erasing ---\n";
    // begin()은 첫 요소를 가리키는 반복자. v.begin() + 1은 두 번째 위치.
    v.insert(v.begin() + 1, 15); 
    printVector("After inserting 15 at index 1: ", v);

    // 20을 찾아서 제거
    auto it = std::find(v.begin(), v.end(), 20);
    if (it != v.end()) { // 요소를 찾았는지 확인
        v.erase(it);
        printVector("After erasing 20: ", v);
    }

    v.pop_back(); // 마지막 요소(30) 제거
    printVector("After pop_back(): ", v);

    // 4. 크기 및 용량 (Size and Capacity)
    std::cout << "\n--- Reserving capacity ---\n";
    v.reserve(100); // 메모리 재할당을 방지하기 위해 공간을 미리 확보
    printVector("After reserving capacity for 100: ", v);
    
    v.push_back(40);
    v.push_back(50);
    printVector("After adding more elements: ", v);

    // 5. 비우기 (Clearing)
    std::cout << "\n--- Clearing the vector ---\n";
    std::cout << "Is vector empty before clear? " << (v.empty() ? "Yes" : "No") << std::endl;
    v.clear(); // 모든 요소 제거
    printVector("After clear(): ", v);
    std::cout << "Is vector empty after clear? " << (v.empty() ? "Yes" : "No") << std::endl;
}