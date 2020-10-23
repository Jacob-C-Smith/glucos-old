MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO | 0x4
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	dd 0x0
	dd 0x0
	dd 0x0
	dd 0x0
	dd 0x0
	dd 0
	dd 1024 ;1920; 
	dd 768  ;1080; 
	dd 32
section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top
 
 	extern kernel_main
	push ebx
	call kernel_main
	cli
.hang:	hlt
	jmp .hang
.end: