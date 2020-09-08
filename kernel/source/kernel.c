#include <typedef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <float.h>

#include <arch/x86/VFS.h>
#include <arch/x86/TTY.h>
#include <arch/x86/MSR.h>
#include <arch/x86/CPUID.h>

void kernel_early(void)
{
	// Initialize TTY, VFS, etc 
	{
		TTY_initialize();
		CPUID_initialize();
		VFS_initialize();
	}
	// Initialize standard library
	{
		// initialize the RNG
		srand(1103515245); //1103515245 as per recommendation of someone... I don't actually rembember who.
                           //The number has something to do with uniform distribution.
		// initialize the memory allocator
		memset((void*)0x1FFFF0, 0, 16);
	}
}

void kernel_main(void) 
{
	kernel_early();
	printf("GlucOS\n");

	FSNode_t* lstdout = findFile("/dev/stdout");
	(lstdout->write)(7,"stdout\n");
	FSNode_t* lstderr = findFile("/dev/random");
	int i = (lstderr->read)(7,"stderr\n");
	printf("%i\n", i);
}