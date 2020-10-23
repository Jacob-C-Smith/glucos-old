#ifndef STDLIB_H
#define STDLIB_H

#include <typedef.h>
#include <NULL.h>

#include <stdio.h>
#include <string.h>
#include <kernel.h>

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0
#define RAND_MAX     0x7FFF

typedef struct {
    int quot, rem;
}div_t;

typedef struct {
    long int quot, rem;
}ldiv_t;

double            atof    ( const char* str );                                                                                          // ❌ Converts the string pointed to, by the argument str to a floating-point number (type double).
int               atoi    ( const char* str );                                                                                          // ❌ Converts the string pointed to, by the argument str to an integer (type int).
long int          atol    ( const char* str );                                                                                          // ❌ Converts the string pointed to, by the argument str to a long integer (type long int).
double            strtod  ( const char* str, char** endptr );                                                                           // ❌ Converts the string pointed to, by the argument str to a floating-point number (type double).
long int          strtol  ( const char* str, char** endptr, int base );                                                                 // ❌ Converts the string pointed to, by the argument str to a long integer (type long int).
unsigned long int strtoul ( const char* str, char** endptr, int base );                                                                 // ❌ Converts the string pointed to, by the argument str to an unsigned long integer (type unsigned long int).
void*             calloc  ( size_t nitems, size_t size );                                                                               // ✔️ Allocates the requested memory and returns a pointer to it.
void              free    ( void *ptr );                                                                                                // ✔️ Deallocates the memory previously allocated by a call to calloc, malloc, or realloc.
void*             malloc  ( size_t size );                                                                                              // ✔️ Allocates the requested memory and returns a pointer to it.
void*             realloc ( void *ptr, size_t size );                                                                                   // ✔️ Attempts to resize the memory block pointed to by ptr that was previously allocated with a call to malloc or calloc.
void              abort   ( void );                                                                                                     // ❌ Causes an abnormal program termination.
int               atexit  ( void (*func)(void) );                                                                                       // ❌ Causes the specified function func to be called when the program terminates normally.
void              exit    ( int status );                                                                                               // ❌ Causes the program to terminate normally.
char*             getenv  ( const char *name );                                                                                         // ❌ Searches for the environment string pointed to by name and returns the associated value to the string.
int               system  ( const char *string );                                                                                       // ❌ The command specified by string is passed to the host environment to be executed by the command processor.
void*             bsearch ( const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *) ); // ❌ Performs a binary search.
void              qsort   ( void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*) );                         // ❌ Sorts an array.
int               abs     ( int x );                                                                                                    // ✔️ Returns the absolute value of x.
div_t             div     ( int numer, int denom );                                                                                     // ✔️ Divides numer (numerator) by denom (denominator).
long int          labs    ( long int x );                                                                                               // ✔️ Returns the absolute value of x.
ldiv_t            ldiv    ( long int numer, long int denom );                                                                           // ✔️ Divides numer (numerator) by denom (denominator).
int               rand    ( void );                                                                                                     // ✔️ Returns a pseudo-random number in the range of 0 to RAND_MAX.
void              srand   ( unsigned int seed );                                                                                        // ✔️ This function seeds the random number generator used by the function rand.

char* itoa ( unsigned int i, char* buffer, int base );

#endif