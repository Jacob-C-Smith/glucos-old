#include <stdlib.h>

//memory allocator structs
struct mallocBlock_s
{
    void*                 where;
    size_t                size;
    u32                   hole;
    struct mallocBlock_s* next;
};
typedef struct mallocBlock_s mallocBlock_t;

//Random number generator values
static int randSeed = 0;
static unsigned long int next = 1;

//Memory allocator values
const mallocBlock_t* mallocBase = (const mallocBlock_t*) 0x1FFFF0;

//itoa
char itoan[16] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F'
};

double atof (const char* str); 
int atoi (const char* str); 
long int atol (const char* str); 

double strtod (const char* str, char** endptr); 
long int strtol (const char* str, char** endptr, int base); 
unsigned long int strtoul (const char* str, char** endptr, int base);

void* calloc (size_t nitems, size_t size)
{
    void* ret = malloc(nitems*size);
    memset(ret,0,nitems*size);
    return ret;
}
void free (void *ptr)
{
    mallocBlock_t* mBase = (mallocBlock_t*) mallocBase;
    while(mBase)
    {
        if(mBase->where == ptr)
        {
            mBase->hole = 1;
            return;
        }
        mBase = mBase->next;
    }
}

void* malloc (size_t size)
{
    mallocBlock_t* mBase      = (mallocBlock_t*) mallocBase;
    static void*   memoryBase = (void*)          0x200000;

    while((size_t)memoryBase < MAX_RAM)
    if(mBase->hole)                                             // Is Hole
    {
        if(mBase->size > size)                                  // Greater than
        {
            size_t slack        =  mBase->size - size;          // Calculate slack
            void*  deltaPointer =  mBase->where + size;         // Calculate the new pointer

            if(mBase->next)                                     // Make and insert a new entry for the slack
            {
                mallocBlock_t* tmBase = mBase;                  // Create a copy of the pointer
                mBase->hole           = 0;
                while(mBase->next)                              // Skip to the end of the list
                    mBase = mBase->next;

                mBase->next = mBase-1;     
                
                mBase->hole  = 1;
                mBase->where = deltaPointer;
                mBase->size  = slack; 
                mBase->next  = 0;
                mBase = tmBase;
            }
            else                                                // Make a new entry for the slack
            {
                mBase->hole  = 0;                               // Flip reservation bit
                mBase->size  = size;                            // Set new size

                mBase->next  = mBase-sizeof(mallocBlock_t);     // Get space for new mallocBlock
                mBase        = mBase->next;                     // set base to point at new base

                mBase->hole  = 1;                               // Flip reservation bit 
                mBase->where = deltaPointer;                    // Set new pointer
                mBase->size  = slack;                           // Set slack
                mBase->next  = NULL;                            // Set NULL
            }
            return mBase->where;
        }
        else if(mBase->size < size)                             // Less than
        {
            if(mBase->next)
                mBase = mBase->next;
            else
            {
                mBase->next = mBase-1;                          // Synthesize a new entry
                mBase       = mBase->next;

                mBase->hole  = 0;
                mBase->next  = NULL;
                mBase->size  = size;
                mBase->where = memoryBase;

                memoryBase   += size;
            }
        }
        else                                                    // Equal to
        {
            mBase->hole = 0;                                    // Flip hole bit
            return mBase->where;                                // Return adress
        }
    }else{                                                      // Isn't Hole
        if(mBase->next) 
            mBase = mBase->next;                                // Next is valid
        else                                                    // Next isn't null
        {
            mBase->next =  mBase-1;
            mBase = mBase->next;

            mBase->hole  = 0;
            mBase->next  = NULL;
            mBase->size  = size;
            mBase->where = memoryBase;

            memoryBase   += size;
            return mBase->where;
        }
    }
    return (void*)0;
    //return OUTOFRAM!
} 

void* realloc (void *ptr, size_t size); 

void abort (void); 
int atexit (void (*func)(void)); 
void exit (int status); 

char* getenv (const char *name); 
int system (const char *string); 

void* bsearch (const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *)); 
void qsort (void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)); 

int abs (int x)
{
    return (x<0) ? x*-1 : x;
}

div_t div (int numer, int denom)
{
    return (div_t) {numer/denom,numer%denom};
}

long int labs (long int x)
{
    return (x>0) ? x*-1 : x;
} 

ldiv_t ldiv (long int numer, long int denom)
{
    return (ldiv_t) {numer/denom,numer%denom};
}

int rand (void)
{
    next = next * randSeed + 12345;
    return (unsigned) (next/2*RAND_MAX) % RAND_MAX+1;
}
void srand (unsigned int seed)
{
    randSeed = seed;
}

char* itoa (unsigned int i, char* buffer, int base)
{
    size_t j = 0;
    if(i == 0)
    {
        buffer[0] = 0;
        buffer[1] = '\0';
        return buffer;
    }

    while(i!=0)
    {
        buffer[j] = itoan[i%base];
        i = i / base;
        j++;
    }
    strrev(buffer);
    return buffer;
}