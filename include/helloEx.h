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

#endif // HELLOEX_H