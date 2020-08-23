#include <stdio.h>

char buffer[32] = "";

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format); 
	while (*format) {
        if(*format == '%')
        {
            format++;
		    if (*format == 'c') {
		    	char c = (char) va_arg(parameters, int);
                TTY_putchar(c);
		    } else if (*format == 's') {
		    	const char* str = va_arg(parameters, const char*);
                TTY_writestring(str);
			} else if (*format == 'i' || *format == 'd') {
				int i = va_arg(parameters, int);
				itoa(i, buffer, 10);
				TTY_writestring(buffer);
		    }else if (*format == 'x') {
				int i = va_arg(parameters, int);
				itoa(i, buffer, 16);
				TTY_writestring(buffer);
		    } else if(*format == '%')
                TTY_putchar('%');
        }else
            TTY_putchar(*format);
        format++;
	}
 
	va_end(parameters);
	return 1;
}