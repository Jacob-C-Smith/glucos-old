/*
 * TTY.h
 * Written by Jacob Smith
 * TTY.h provides functions for teletype devices
 */

#ifndef X86_TTY_H
#define X86_TTY_H

#include <typedef.h>
#include <string.h>

#include <arch/x86/VGA.h>

void TTY_initialize  ( void );                                 // Clears the VGA text mode memory, sets cursor to 0,0, white on black
void TTY_setcolor    ( u8 color );                             // Sets the color of the terminal
void TTY_putentryat  ( char c, u8 color, size_t x, size_t y ); // Puts character c at x,y in color color.
void TTY_putchar     ( char c );                               // Prints character c
void TTY_write       ( size_t size, const char* data );        // Prints size bytes of data
void TTYF_write      ( size_t size, void* data );              // Prints size bytes of data
void TTYE_write      ( size_t size, void* data );              // Prints size bytes of data, but in light red on black
void TTY_writestring ( const char* data );                     // Prints string at data until null terminator
 
#endif