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
    int    (*read)  (size_t length, void* buffer);
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
    char* write;
    char* bufferBase;

    FSNode_t* fsn;
};

extern FSNode_t* fsRoot;

void      VFS_initialize();                                                // Creates the /dev directory and populates it with
                                                                           // stdout, stderr, stdin, random, zero, and null

FSNode_t* createFile    (const char* name, u32 flags,                      // Allocates for and creates a file
                         u32 length, int (*read) (),                       // with specified attributes    
                         void (*write) (size_t length, void* buffer),    
                         int (*open) (), int (*close) (),              
                         struct FSNode_s* contents, struct FSNode_s* next);

FSNode_t* findFile      (const char* path);                                // Searches the VFS for a file

size_t    open          (const char* path, size_t oFlag, size_t oMode);
size_t    close         (FSNode_t* fn);
size_t    read          (FSNode_t* fn, void* buf, size_t count);
size_t    write         (FSNode_t* fn, const void* buf, size_t nBytes);


#endif