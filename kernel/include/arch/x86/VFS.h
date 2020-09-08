#ifndef X86_VFS_H
#define X86_VFS_H

#include <typedef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <arch/x86/TTY.h>

#define lineBuffered       0x0001
#define unbuffered         0x0002
#define OKToRead           0x0004
#define OKToWrite          0x0008
#define OpenForReading     0x0010
#define foundEOF           0x0020
#define foundError         0x0040
#define bufFromMalloc      0x0080
#define openedInAppendMode 0x0100
#define sprintfString      0x0200

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
    char   name[128];
    u32    flags;
    u32    length;
    int    (*read)  ();
    void   (*write) (size_t length, void* buffer);
    int    (*open)  ();
    int    (*close) ();
    struct FSNode_s* contents;
    struct FSNode_s* next;
};
typedef struct FSNode_s FSNode_t;

struct sFILE
{
    int   flags;
    
    char* read;
    char* readEnd;
    char* readBase;

    char* write;
    char* writeEnd;
    char* writeBase;
    
    char* bufferBase;
    char* bufferEnd;

    FSNode_t* fsn;
};

extern FSNode_t* fsRoot;

void      VFS_initialize();
FSNode_t* createFile    (const char* name, u32 flags,u32 length,int (*read) (), \
                         void (*write) (size_t length, void* buffer),int (*open) (), \
                         int (*close) (), struct FSNode_s* contents, struct FSNode_s* next);
FSNode_t* findFile      (const char* path);

#endif