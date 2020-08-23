#include <VFS.h>

FSNode_t* fsRoot;

void initVFS()
{
    FSNode_t* dev    = calloc(sizeof(FSNode_t),1);
    FSNode_t* tty0   = calloc(sizeof(FSNode_t),1);

    fsRoot = malloc(sizeof(FSNode_t));
    fsRoot->flags    = FSN_mountPoint;
    fsRoot->contents = dev;
    
    dev->flags    = FSN_directory;
    dev->contents = tty0;
    dev->write    = TTY_write;
    dev->read     = NULL;
    dev->close    = NULL;
    dev->open     = NULL;
}