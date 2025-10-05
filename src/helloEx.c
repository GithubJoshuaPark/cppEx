#include <stdio.h>
#include <string.h> // For strlen
#include "helloEx.h"

void say_hello(void) {
    printf("Hello, World from C!\n");
}

/**
 * Prints a line with dashes above and below it.
 */
void printLine(const char* line) {
    if (line != NULL) {
        size_t len = strlen(line);
        // print '-'  with the provided line length times
        for (size_t i = 0; i < len; i++) {
            putchar('-');
        }
        putchar('\n');
        printf("%s\n", line); // The original string in hello.c already has a newline
        for (size_t i = 0; i < len; i++) {
            putchar('-');
        }
        putchar('\n');
        
    } else {
        printf("NULL line provided.\n");
    }
}
