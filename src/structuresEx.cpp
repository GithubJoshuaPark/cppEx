#include <iostream>
#include "helloEx.h" // Note: This file uses C-style printf
#include "structuresEx.h"

// 1. Define a structure. This is a blueprint for a new data type.
// It groups related variables under a single name.
typedef struct Student {
    char name[50];
    int student_id;
    float gpa;
} Student;

void structuresEx(void) {
    printLine("Demonstrating Structures");

    // 2. Declare a variable of our new 'struct Student' type.
    Student student1;

    // 3. Assign values to the members of the structure using the dot (.) operator.
    // For strings, we must use a function like strcpy to copy the value.
    strcpy(student1.name, "John Doe");
    student1.student_id = 12345;
    student1.gpa = 3.8f;

    // 4. Access and print the values of the structure members.
    std::cout << "-----------------------" << std::endl;
    std::cout << "Student Information:" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "Student Name: " << student1.name << std::endl;
    std::cout << "Student ID. : " << student1.student_id << std::endl;
    std::cout << "Student GPA : " << student1.gpa << std::endl;

}