#include <arch/x86/VFS.h>
FSNode_t* fsRoot;

void VFS_initialize( )
{
    /*
     * This is what the VFS looks like after the initialization function. In
     * GlucOS, /dev/stdout prints to VGA memory, as defined in 
     * arch/x86/TTY.h and arch/x86/VGA.h. /dev/stderr prints to VGA memory, 
     * but in the color red. TODO: /dev/stdin will read from a PS/2 keyboard
     * 
     * /
     * └── dev
     *     ├── stdout     - standard library output
     *     ├── stdin      - standard library input
     *     ├── stderr     - standard library error
     *     ├── random     - pseudo random number generator, returns FULL when written to
     *     ├── zero       - accepts and discards all input written to it; produces a continuous stream of null characters (zero-value bytes) as output when read from.
     *     └── null       - accepts and discards all input written to it; provides an end-of-file indication when read from.
     */

    FSNode_t* dev     = createFile("dev"   , FSN_directory , 0, NULL       , NULL       , NULL, NULL, NULL, NULL);
    FSNode_t* lstdout = createFile("stdout", FSN_charDevice, 0, NULL       , &TTYF_write, NULL, NULL, NULL, NULL);
    FSNode_t* lstdin  = createFile("stdin" , FSN_charDevice, 0, NULL       , NULL       , NULL, NULL, NULL, NULL);
    FSNode_t* lstderr = createFile("stderr", FSN_charDevice, 0, NULL       , &TTYE_write, NULL, NULL, NULL, NULL);
    FSNode_t* lrandom = createFile("random", FSN_charDevice, 0, &rand      , NULL       , NULL, NULL, NULL, NULL);
    FSNode_t* lzero   = createFile("zero"  , FSN_charDevice, 0, NULL/*&returnNULL*/,NULL /*&eatInput*/  , NULL, NULL, NULL, NULL);
    FSNode_t* lnull   = createFile("null"  , FSN_charDevice, 0, NULL       , NULL/*&eatInput*/  , NULL, NULL, NULL, NULL);

    fsRoot            = dev;
    dev->contents     = lstdout;
    lstdout->next     = lstdin;
    lstdin->next      = lstderr;
    lstderr->next     = lrandom;
    lrandom->next     = lzero;
    lzero->next       = lnull;
    lnull->next       = NULL;
}

FSNode_t* createFile( const char* name, u32 flags, u32 length,int (*read) (),void (*write) (size_t length, void* buffer),int (*open) (),int (*close) (), struct FSNode_s* contents, struct FSNode_s* next )
{
    FSNode_t* ret = malloc(sizeof(FSNode_t));
    
    if(strlen(name) >= 128)
        return NULL;

    strcpy(ret->name, name);

    ret->flags    = flags;
    ret->length   = length;
    ret->read     = read;
    ret->write    = write;
    ret->open     = open;
    ret->close    = close;
    ret->contents = contents;
    ret->next     = next;

    return ret;
}

FSNode_t* findFile( const char* path )
{
    FSNode_t* root = fsRoot;

    char* t;
    char* pCopy = malloc(strlen(path));

    strcpy(pCopy, path);
    t = strtok(pCopy, "/");
    while(t)
    {
        if(strcmp(root->name, t) == 0)
        {
            t = strtok(NULL, "/");
            if(t)
            {
                root = root->contents;
                continue;
            }else{
                free(pCopy);
                return root;
            }
        }
        if(root->next)
            root = root->next;
        else
        {
            free(pCopy);
            return NULL;
        }
    }

    free(pCopy);
    return NULL;
}

size_t open ( const char* path, size_t oFlag, size_t oMode )
{
    FSNode_t* ret = findFile(path);
    return (ret->open)();
}

size_t close ( FSNode_t* fn )
{
    return (fn->close)();
}

size_t read ( FSNode_t* fn, void* buf, size_t count )
{
    return (fn->read)(count,buf);
}

size_t write ( FSNode_t* fn, void* buf, size_t count )
{
    return (fn->write)(count,buf);
}
