#ifndef X86_GDT_H
#define X86_GDT_H

#include <typedef.h>

#include <stdlib.h>


//0xbbflaabbbbbbffff
//0x00CF9A0
//00000FFFF
//0x00CF9A000000FFFF

#define GDT_PRESENT    0x80
#define GDT_PRIV_L0    0x00
#define GDT_PRIV_L1    0x20
#define GDT_PRIV_L2    0x40
#define GDT_PRIV_L3    0x60
#define GDT_CODEDATA   0x10
#define GDT_EXECUTABLE 0x08
#define GDT_DIRECTION  0x04
#define GDT_WRITE      0x02
#define GDT_ACCESS     0x01

#define GDT_GRANUL     0x08
#define GDT_32PM       0x04

#define CODEPL0 GDT_PRESENT | GDT_PRIV_L0 | GDT_CODEDATA | GDT_EXECUTABLE | 0 | GDT_WRITE | 0
#define DATAPL0 GDT_PRESENT | GDT_PRIV_L0 | GDT_CODEDATA | 0              | 0 | GDT_WRITE | 0
#define CODEPL3 GDT_PRESENT | GDT_PRIV_L3 | GDT_CODEDATA | GDT_EXECUTABLE | 0 | GDT_WRITE | 0
#define DATAPL3 GDT_PRESENT | GDT_PRIV_L3 | GDT_CODEDATA | 0              | 0 | GDT_WRITE | 0

#define ACCESS  GDT_GRANUL  | GDT_32PM

u64 GDTCreateDescriptor( size_t base, size_t limit, u8 access, u8 flags )
{
    u64 ret = 0;

    ret |= base           & 0xFF000000;
    ret |= (flags  << 20) & 0x00F00000;
    ret |= (limit  << 16) & 0x000F0000;
    ret |= (access <<  8) & 0x0000FF00;
    ret |= (base   >> 16) & 0x000000FF;

    ret >>= 32;

    ret |= base           & 0xFFFF0000;
    ret |= limit          & 0x0000FFFF;

    return ret;
}

void GDT_initialize ( ) {
    unsigned long long* GDT = malloc(sizeof(u64)*5);
    GDT[0] = GDTCreateDescriptor(0x00000000,0x00000000,0x00  ,0x00   );
    GDT[1] = GDTCreateDescriptor(0x00000000,0xFFFFFFFF,ACCESS,CODEPL0);
    GDT[2] = GDTCreateDescriptor(0x00000000,0xFFFFFFFF,ACCESS,DATAPL0);
    GDT[3] = GDTCreateDescriptor(0x00000000,0xFFFFFFFF,ACCESS,CODEPL3);
    GDT[4] = GDTCreateDescriptor(0x00000000,0xFFFFFFFF,ACCESS,DATAPL3);

}

#endif