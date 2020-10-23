#include <typedef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <float.h>

#include <GlucOS/VBE.h>
#include <GlucOS/UI.h>

#include <arch/x86/VFS.h>
#include <arch/x86/TTY.h>
#include <arch/x86/GDT.h>
#include <arch/x86/MSR.h>
#include <arch/x86/CPUID.h>
#include <arch/x86/multiboot.h>


void kernel_early(multiboot_info_t* multiHeader)
{
	// Initialize TTY, GDT, VFS, etc 
	{
		TTY_initialize();
		VBE_initialize(multiHeader->framebuffer_addr, multiHeader->framebuffer_width, multiHeader->framebuffer_height, multiHeader->framebuffer_bpp);
		GDT_initialize();
		CPUID_initialize();
		VFS_initialize();
	}
	// Initialize standard library
	{
		// initialize the RNG
		srand(1103515245); //1103515245 as per recommendation of someone... I don't actually rembember who. The number has something to do with uniform distribution.
		// initialize the memory allocator
		memset((void*)0x1FFFF0, 0, 16);
	}
}

void kernel_main(multiboot_info_t* multiHeader) 
{
	kernel_early(multiHeader);
	UIDesktop_t* desktop = UICreateDesktop();
	UIAppendWindow(desktop, UICreateWindow("Window 1",20,20,200,200));
	UIAppendWindow(desktop, UICreateWindow("Window 2",100,100,200,200));
	UIAppendWindow(desktop, UICreateWindow("Window 3",200,200,200,200));
	UIDrawDesktop(desktop);

	UILabel_t* label = UICreateLabel("label","label",42,10,500,500);
	UIDrawLabel(label);
}