#include <stdio.h>

char buffer[32] = "";

#define FILEFlagRead        0x1  // read
#define FILEFlagWrite       0x2  // write
#define FILEFlagAppend      0x4  // append
#define FILEFlagUpdate      0x8  // update
#define FILEFlagBinary      0x10 // binary
#define FILEFlagFailOnExist 0x20 // fails if file exists
#define FILEFlagMustExist   0x40 // fails if file doesn't exist
/*
FILE* fopen(const char* filename, const char* mode)
{
	FILE* ret = malloc(sizeof(file))
	ret->fileNode = findFile(filename);
	size_t i = 0;
	while(mode[++i])
		switch (mode[i])
		{
		case 'r':                                                  // read
			ret->flags |= FILEFlagRead;
			break;
		case 'w':                                                  // write
			ret->flags |= FILEFlagWrite;
			break;
		case 'a':                                                  // append
			ret->flags |= FILEFlagAppend;
			break;
		case '+':                                                  // update
			if(ret->flags & FILEFlagRead)                          // "r+"
				ret->flags |= FILEFlagWrite | FILEFlagMustExist;
			else if(ret->flags & FILEFlagWrite)                    // "w+"
				ret->flags |= FILEFlagRead;
			else if(ret->flags & FILEFlagAppend)                   // "a+"
				ret->flags |= FILEFlagRead | FILEFlagWrite;
			break;
		case 'b':                                                  // binary
			ret->flags |= FILEFlagBinary;
			break;
		case 'x':                                                  // fail if exists
			ret->flags |= FILEFlagMustExist;
			break;
		default:
			break;
		}
	ret->fileNode = findFile(path);
	if(ret->flags & FILEFlagFailOnExist){
		if(ret->fileNode)
			return NULL;
	}else if(ret->flags & FILEFlagMustExist)
	{
		if(ret->fileNode == NULL)
			return NULL;
	}
}*/

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format); 
	while (*format) {
        if(*format == '%')
        {
            format++;
		    if (*format == 'c') {
		    	char c = (char) va_arg(parameters, int);
                VBE_putchar(c);
		    } else if (*format == 's') {
		    	const char* str = va_arg(parameters, const char*);
                VBE_writestring(str);
			} else if (*format == 'i' || *format == 'd') {
				int i = va_arg(parameters, int);
				itoa(i, buffer, 10);
				VBE_writestring(buffer);
		    }else if (*format == 'x') {
				int i = va_arg(parameters, int);
				itoa(i, buffer, 16);
				VBE_writestring(buffer);
		    } else if(*format == '%')
                VBE_putchar('%');
        }else
            VBE_putchar(*format);
        format++;
	}

	va_end(parameters);
	return 1;
}
