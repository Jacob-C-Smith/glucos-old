#include <typedef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arch/x86/TTY.h>

void kernel_early(void)
{
	// initialize TTY, VFS, etc initialization
	TTY_initialize();
	// initialize standard library
	// initialize the RNG
	srand(1103515245);
	// initialize the memory allocator
	memset((void*)0x1FFFF0, 0, 16);
}

void kernel_main(void) 
{
	kernel_early();
	
}