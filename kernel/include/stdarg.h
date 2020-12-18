#ifndef STDARG_H
#define STDARG_H

#define va_start(ap,parmn) (void)((ap) = (char*)(&(parmn) + 1))
#define va_end(ap) (void)((ap) = 0)
#define va_arg(ap,ttype) (((ttype*)((ap) = ((ap) + sizeof(ttype))))[-1])

typedef char* va_list;


#endif