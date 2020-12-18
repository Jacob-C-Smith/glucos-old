/*
 * GLUI.h
 * Written by Jacob Smith
 * GLUI.h provides functions for VBE devices
 */

#ifndef X86_VBE_GRAPHICS_H
#define X86_VBE_GRAPHICS_H

#include <typedef.h>
#include <stdlib.h>

struct VBEScreen_s{
    u32* framebufferAddress;
    u32 width;
    u32 height;
    u8 colorDepth;
};
typedef struct VBEScreen_s VBEScreen_t;

VBEScreen_t*  VBE_initialize    ( void* frameBufferAddr, u32 width, u32 height, u8 colorDepth ); // Clears the VBE memory, sets cursor to 0,0, black on white
void          VBE_putPixel      ( u32 color, size_t x, size_t y );                               // Puts a pixel at x,y in color color.
void          VBE_putcharat     ( char c, size_t x, size_t y, u32 color );                       // Puts character c at x,y in color color.
void          VBE_putchar       ( char c );                                                      // Prints character c
void          VBE_write         ( size_t size, const char* data );                               // Prints size bytes of data
void          VBE_writestringat ( const char* data, size_t x, size_t y );                        // Prints string at (x,y) from data until null terminator
void          VBE_writestring   ( const char* data );                                            // Prints string at data until null terminator
void          VBE_drawRect      ( u32 x, u32 y, u32 w, u32 h, u32 c );                           // Draws a rectangle at (x,y) with (w,h) size and c color
void          VBE_drawLine      ( u32 x0, u32 y0, u32 x1, u32 y1, u32 c );                       // Draws a line from (x0, y0) to (x1, y1) with c color
void          VBE_drawHollowRect( u32 x, u32 y, u32 w, u32 h, u32 c );                           // Draws a hollow rectangle at (x,y) with (w,h) size and c color

#endif