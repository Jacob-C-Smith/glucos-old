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
		VBE_initialize((void*)multiHeader->framebuffer_addr, multiHeader->framebuffer_width, multiHeader->framebuffer_height, multiHeader->framebuffer_bpp);
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
	UIAppendWindow(desktop, UICreateWindow("Window 1",50,50,301,111));
	UIDrawDesktop(desktop);

	char* options[4] = {"Option 1", "Option 2", "Option 3", (char*)0};
	UIDropdown_t* aa = UICreateDropdown("AW", options, 50+46, 50+25, 78, 12);
	UIDrawDropdown(aa);
	
	UIDropdown_t* bb = UICreateDropdown("AW", options, 50+46, 50+44, 78, 12);
	bb->collapsed = false;
	UIDrawDropdown(bb);

	UICheckbox_t* cc = UICreateCheckbox("AW","AW",50+190,50+25);
	cc->checked = true;
	UICheckbox_t* dd = UICreateCheckbox("AW","AW",50+190,50+39);
	UICheckbox_t* ee = UICreateCheckbox("AW","AW",50+190,50+53);
	ee->checked = true;

	UIDrawCheckbox(cc);
	UIDrawCheckbox(dd);
	UIDrawCheckbox(ee);

	UILabel_t* ccl = UICreateLabel("AW","Magnesium",50+205,50+27);
	UILabel_t* ddl = UICreateLabel("AW","Aluminum",50+205,50+41);
	UILabel_t* eel = UICreateLabel("AW","NiChrome",50+205,50+55);	

	UIDrawLabel(ccl);
	UIDrawLabel(ddl);
	UIDrawLabel(eel);

	
	UIButton_t* ff = UICreateButton("AW","Button",50+146,50+70, 51,12);
	UIButton_t* gg = UICreateButton("AW","Button",50+146,50+70, 51,12);

	UIDrawButton(ff);
	UIDrawButton(gg);

	
	UITextInput_t* hh = UICreateTextInput("AW", "First Name",50+200,50+69,85, 16);
	UIDrawTextInput(hh);

	UILabel_t* ii = UICreateLabel("AW", "label", 50+168,50+88);
	UIDrawLabel(ii);
}