#ifndef HELLOEX_H
#define HELLOEX_H

#include <stdio.h>
 
// When a C++ compiler includes this header, it needs to know that these
// functions have C linkage (no name mangling). The __cplusplus macro
// is only defined by C++ compilers.
#ifdef __cplusplus
extern "C" {
#endif
 
void say_hello(void);
void printLine(const char* line);
 
#ifdef __cplusplus
}
#endif


// 1. Define an enumeration (enum).
// Enums assign names to integer constants, making code more readable.
// By default, SUNDAY is 0, MONDAY is 1, and so on.
typedef enum Day {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
} Day;

typedef struct Student {
    char name[50];
    int student_id;
    float gpa;
} Student;

typedef struct Vector2D {
    float x;
    float y;
} Vector2D;

// All members of a union share the same memory location.
// The size of the union is determined by the size of its largest member.
typedef union Data {
    int i;
    float f;
    char str[20];
} Data;

#endif // HELLOEX_H