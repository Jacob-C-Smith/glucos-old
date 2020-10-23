#ifndef STDDEF_H
#define STDDEF_H

#include <NULL.h>

#define offsetof( structure, member ) \
    ((size_t)((char *)&((structure *)0)->member - (char *)0))

#endif