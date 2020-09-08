#ifndef X86_MSR_H
#define X86_MSR_H

#include <typedef.h>

static inline u64 readTimestamp()
{
    u64 ret;
    asm volatile ( "rdtsc" : "=A"(ret) );
    return ret;
}

#endif