#ifndef STDIO_H
#define STDIO_H

#include <typedef.h>
#include <NULL.h>
#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>

#include <arch/x86/VFS.h>
#include <arch/x86/TTY.h>

struct fpos_s
{

};
typedef struct fpos_s fpos_t;

#define IOFBF 0
#define IOLBF 1
#define IONBF 2

#define BUFSIZE 512
#define EOF (-1) 

#define FOPEN_MAX    3     // This is an admittedly arbitrary choice, and I can probably expand in the future. For now, this will make debugging easier and I don't really need to open many files at a time
#define FILENAME_MAX 16350 // Max for SFS
#define TMP_MAX            

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define stdin
#define stdout
#define stderr

int      fclose   (FILE* stream);                                             // ❌ Closes the stream. All buffers are flushed.
void     clearerr (FILE* stream);                                             // ❌ Clears the end-of-file and error indicators for the given stream.
int      feof     (FILE* stream);                                             // ❌ Tests the end-of-file indicator for the given stream.
int      ferror   (FILE* stream);                                             // ❌ Tests the error indicator for the given stream.
int      fflush   (FILE* stream);                                             // ❌ Flushes the output buffer of a stream.
int      fgetpos  (FILE* stream, fpos_t* pos);                                // ❌ Gets the current file position of the stream and writes it to pos.
FILE*    fopen    (const char* filename, const char* mode);                   // ❌ Opens the filename pointed to by filename using the given mode.
size_t   fread    (void* ptr, size_t size, size_t nmemb, FILE* stream);       // ❌ Reads data from the given stream into the array pointed to by ptr.
FILE*    freopen  (const char* filename, const char* mode, FILE* stream);     // ❌ Associates a new filename with the given open stream and same time closing the old file in stream.
int      fseek    (FILE* stream, long int offset, int whence);                // ❌ Sets the file position of the stream to the given offset. The argument offset signifies the number of bytes to seek from the given whence position.
int      fsetpos  (FILE* stream, const fpos_t* pos);                          // ❌ Sets the file position of the given stream to the given position. The argument pos is a position given by the function fgetpos.
long int ftell    (FILE* stream);                                             // ❌ Returns the current file position of the given stream.
size_t   fwrite   (const void* ptr, size_t size, size_t nmemb, FILE* stream); // ❌ Writes data from the array pointed to by ptr to the given stream.
int      remove   (const char* filename);                                     // ❌ Deletes the given filename so that it is no longer accessible.
int      rename   (const char* old_filename, const char* new_filename);       // ❌ Causes the filename referred to, by old_filename to be changed to new_filename.
void     rewind   (FILE* stream);                                             // ❌ Sets the file position to the beginning of the file of the given stream.
void     setbuf   (FILE* stream, char* buffer);                               // ❌ Defines how a stream should be buffered.
int      setvbuf  (FILE* stream, char* buffer, int mode, size_t size);        // ❌ Another function to define how a stream should be buffered.
FILE*    tmpfile  (void);                                                     // ❌ Creates a temporary file in binary update mode (wb+).
char*    tmpnam   (char* str);                                                // ❌ Generates and returns a valid temporary filename which does not exist.
int      fprintf  (FILE* stream, const char* format, ...);                    // ❌ Sends formatted output to a stream.
int      printf   (const char* format, ...);                                  // ❌ Sends formatted output to stdout.
int      sprintf  (char* str, const char* format, ...);                       // ❌ Sends formatted output to a string.
int      vfprintf (FILE* stream, const char* format, va_list arg);            // ❌ Sends formatted output to a stream using an argument list.
int      vprintf  (const char* format, va_list arg);                          // ❌ Sends formatted output to stdout using an argument list.
int      vsprintf (char* str, const char* format, va_list arg);               // ❌ Sends formatted output to a string using an argument list.
int      fscanf   (FILE* stream, const char* format, ...);                    // ❌ Reads formatted input from a stream.
int      scanf    (const char* format, ...);                                  // ❌ Reads formatted input from stdin.
int      sscanf   (const char* str, const char* format, ...);                 // ❌ Reads formatted input from a string.
int      fgetc    (FILE* stream);                                             // ❌ Gets the next character (an unsigned char) from the specified stream and advances the position indicator for the stream.
char*    fgets    (char* str, int n, FILE* stream);                           // ❌ Reads a line from the specified stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.
int      fputc    (int c, FILE* stream);                                      // ❌ Writes a character (an unsigned char) specified by the argument char to the specified stream and advances the position indicator for the stream.
int      fputs    (const char* str, FILE* stream);                            // ❌ Writes a string to the specified stream up to but not including the null character.
int      getc     (FILE* stream);                                             // ❌ Gets the next character (an unsigned char) from the specified stream and advances the position indicator for the stream.
int      getchar  (void);                                                     // ❌ Gets a character (an unsigned char) from stdin.
char*    gets     (char* str);                                                // ❌ Reads a line from stdin and stores it into the string pointed to by, str. It stops when either the newline character is read or when the end-of-file is reached, whichever comes first.
int      putc     (int c, FILE* stream);                                      // ❌ Writes a character (an unsigned char) specified by the argument char to the specified stream and advances the position indicator for the stream.
int      putchar  (int c);                                                    // ❌ Writes a character (an unsigned char) specified by the argument char to stdout.
int      puts     (const char* str);                                          // ❌ Writes a string to stdout up to but not including the null character. A newline character is appended to the output.
int      ungetc   (int c, FILE* stream);                                      // ❌ Pushes the character c (an unsigned char) onto the specified stream so that the next character is read.
void     perror   (const char* str);                                          // ❌ Prints a descriptive error message to stderr. First the string str is printed followed by a colon and then a space.

#endif