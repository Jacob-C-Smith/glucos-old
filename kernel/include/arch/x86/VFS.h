#ifndef VFS_H
#define VFS_H

#include <typedef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum FSNodeFlags {
    FSN_file         = 1,
    FSN_directory    = 2,
    FSN_charDevice   = 3,
    FSN_blockDevice  = 4,
    FSN_pipe         = 5,
    FSN_symbolicLink = 6,
    FSN_mountPoint   = 7,
    FSN_socket       = 8
};

struct FSNode_s
{
    char name[128];
    u8   flags;
    u32  length;
    int  (*read)  ();
    void (*write) (size_t length, void* buffer);
    int  (*open)  ();
    int  (*close) ();
    struct FSNode_s* contents;
    struct FSNode_s* next;
};
typedef struct FSNode_s FSNode_t;
typedef struct FSNode_s FILE;

extern FSNode_t* fsRoot;


void initVFS();

#endif