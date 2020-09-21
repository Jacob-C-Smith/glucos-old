#ifndef X86_VGA_H
#define X86_VGA_H

#include <typedef.h>

#define videoMem   0xB8000

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

enum vga_color {
	black        = 0,
	blue         = 1,
	green        = 2,
	cyan         = 3,
	red          = 4,
	magenta      = 5,
	brown        = 6,
	lightGrey    = 7,
	darkGrey     = 8,
	lightBlue    = 9,
	lightGreen   = 10,
	lightCyan    = 11,
	lightRed     = 12,
	lightMagenta = 13,
	lightBrown   = 14,
	white        = 15,
};

static inline u8 vga_entry_color(u8 fg,  u8 bg) 
{
	return fg | bg << 4;                          // Bits 0-3 are foreground, bits 4-7 are background.
}
 
static inline u16 vga_entry(u8 uc, u8 color) 
{
	return (u16) uc | (u16) color << 8;           // Bits 0-7 are character, bits 8-15 are color attribute.
}
 

#endif