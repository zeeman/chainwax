#ifndef UTILS_H
#define UTILS_H


#include <stdio.h>


static inline
void ensure(int test, char* error_str)
{
    if (!test) {
        fputs(error_str, stderr);
        exit(1);
    };
}


static inline
void die()
{
    exit(1);
}


#endif // UTILS_H
