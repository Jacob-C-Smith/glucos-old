#include <time.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <arch/x86/MSR.h>

const char* months[12] = {
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
};

const char* days[7] = {
    "Sun",
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat"
};

char ASCIITime[24];
char tBuffer[5];
char* asctime (const struct tm* timeptr); //Day Mon Day HH:MM:SS YYYY
clock_t clock (void)
{
    return readTimestamp();
}
char* ctime ( const time_t* timer );
double difftime ( time_t time1, time_t time2 );
struct tm* gmtime ( const time_t* timer );
struct tm* localtime ( const time_t* timer );
time_t mktime ( struct tm* timeptr );
size_t strftime ( char* str, size_t maxsize, const char* format, const struct tm* timeptr );
time_t time ( time_t* timer );