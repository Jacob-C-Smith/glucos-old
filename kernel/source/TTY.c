#include <arch/x86/TTY.h>

size_t TTY_row;
size_t TTY_column;
u8     TTY_color;
u16*   TTY_buffer;
 
void TTY_initialize(void) 
{
	TTY_row    = 0;
	TTY_column = 0;
	TTY_color  = vga_entry_color(white, black);
	TTY_buffer = (u16*) videoMem;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			TTY_buffer[index] = vga_entry(' ', TTY_color);
		}
	}
}
 
void TTY_setcolor(u8 color) 
{
	TTY_color = color;
}
 
void TTY_putentryat(char c, u8 color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	TTY_buffer[index] = vga_entry(c, color);
}
 
void TTY_putchar(char c) 
{
	if(c == '\n')
    {
        if(++TTY_row > 24)
		{
			memcpy((void*)0xB8000,(void*)0xB80A0,0xf00);
			memset((void*)0xB8F00,0,0xA0);
			TTY_row = 24;
		}
        TTY_column = 0;
        return;
    }
	TTY_putentryat(c, TTY_color, TTY_column, TTY_row);
	if (++TTY_column == VGA_WIDTH) {
		TTY_column = 0;
		if (++TTY_row == VGA_HEIGHT)
			TTY_row = 0;
	}
}
 
void TTY_write(size_t size, const char* data) 
{
	for (size_t i = 0; i < size; i++)
		TTY_putchar(data[i]);
}
 
void TTY_writestring(const char* data) 
{
	TTY_write(data, strlen(data));
}
 