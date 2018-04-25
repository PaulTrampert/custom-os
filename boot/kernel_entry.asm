global _start
[bits 32]
[extern kernel_main] ; Define the calling point. Must have the same name as kernel.c 'main' function
_start:
push eax
push ebx
call kernel_main ; Calls the C function. The linker will know where it is placed in memory
jmp $