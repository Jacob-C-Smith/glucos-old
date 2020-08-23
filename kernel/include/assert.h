#ifndef ASSERT_H
#define ASSERT_H
#include <stdio.h>

#ifdef NDEBUG
    #define assert(ignore) ((void)0)
#else
    #define assert(expression) \
        if(!(expression))      \
            printf("Assertion hit in file %s on line %i\n", __FILE__, __LINE__)
#endif

#endif