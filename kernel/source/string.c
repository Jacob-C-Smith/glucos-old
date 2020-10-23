#include <string.h>

char* errorMessages [] = {
	"Division by zero"
};

void* memchr ( const void *str, int c, size_t n )
{
	unsigned char *p = (unsigned char*)str;
    while( n-- )
        if( *p != (unsigned char)c )
            p++;
        else
            return p;
    return 0;
}

int memcmp ( const void *str1, const void *str2, size_t n )
{
    const unsigned char *p1 = str1, *p2 = str2;
    while(n--)
        if( *p1 != *p2 )
            return *p1 - *p2;
        else
            p1++,p2++;
    return 0;
}

void* memcpy ( void *dest, const void *src, size_t n )
{
    char *dp = dest;
    const char *sp = src;
    while (n--)
        *dp++ = *sp++;
    return dest;
}

void* memmove ( void *dest, const void *src, size_t n )
{
    return memcpy(dest,src,n);
}

void* memset ( void *str, int c, size_t n )
{
    unsigned char* p=str;
    while(n--)
        *p++ = (unsigned char)c;
    return str;
}

char* strcat ( char *dest, const char *src )
{
	return strncat(dest,src,strlen(src));
}

char* strncat ( char *dest, const char *src, size_t n )
{
	strncpy(&dest[strlen(dest)],src,n);
	return dest;
}

char* strchr ( const char *str, int c )
{
	for (; *str != '\0'; ++str)
		if (*str == c)
			return (char *) str;
	return NULL;
}

int strcmp ( const char *str1, const char *str2 )
{
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t ret = (len1 > len2) ? len1 : len2;
	return strncmp(str1,str2,ret);
}

int strncmp ( const char *str1, const char *str2, size_t n )
{
	for (size_t i = 0; i < n; i++)
		if(str1[i] ^ str2[i])
			return (str1[i] > str2[i]) ? 1 : -1;
	return 0;
}

int strcoll ( const char *str1, const char *str2 ); 

char* strcpy (char *dest, const char *src)
{
	return strncpy(dest,src,strlen(src));
}
char* strncpy ( char *dest, const char *src, size_t n )
{
	for (size_t i = 0; i < n; i++)
		dest[i] = src[i];
	return dest;
}

size_t strcspn ( const char *str1, const char *str2 )
{
    size_t ret=0;
    while(*str1)
	{
        if(strchr(str2,*str1))
            return ret;
        else
            str1++,ret++;
	}
	return ret;
};

char* strerror ( int errnum )
{
	return errorMessages[errnum];
}

size_t strlen ( const char* str ) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

char* strpbrk ( const char *str1, const char *str2 )
{
	while(*str1)
        if(strchr(str2, *str1++))
            return (char*)--str1;
    return 0;
}

char* strrchr ( const char *str, int c )
{
    char* ret=0;
    do {
        if( *str == (char)c )
            ret=(char*)str;
    } while(*str++);
    return ret;
}

size_t strspn ( const char *str1, const char *str2 )
{
	size_t ret=0;
    while(*str1 && strchr(str2,*str1++))
        ret++;
    return ret;   
}

char* strstr ( const char *haystack, const char *needle )
{
	size_t n = strlen(needle);
    while(*haystack)
        if(!memcmp(haystack++,needle,n))
            return (char*)haystack-1;
    return 0;
}

char* strtok ( char *str, const char *delim )
{
	static char* p=0;
    if(str)
        p=str;
    else if(!p)
        return 0;
    str=p+strspn(p,delim);
    p=str+strcspn(str,delim);
    if(p==str)
        return p=0;
    p = *p ? *p=0,p+1 : 0;
    return str;
}

size_t strxfrm ( char *dest, const char *src, size_t n ); 

char* strrev( char* str )
{
    int a, b;
    char c;
    size_t len = strlen((const char*)str);
    for(a=0,b=len-1; a<b;a++,b--)
    {
        c = str[a];
        str[a] = str[b];
        str[b] = c;
    }
    return str;
}