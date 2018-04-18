[org 0x7c00] ; bootloader offset
KERNEL_OFFSET equ 0x1000 ; The address used when linking

    mov [BOOT_DRIVE], dl ; BIOS gives us the boot drive in 'dl' on boot
    mov bp, 0x9000 ; set the stack
    mov sp, bp

    ; Write message after BIOS messages
    mov bx, MSG_REAL_MODE
    call print
    call print_nl

    call load_kernel   ; read the kernel from disk
    call switch_to_pm  ; disable interrupts, load GDT, etc. Finally jumps to BEGIN_PM
    jmp $ ; this should never be called

%include "boot/boot_sect_print.asm"
%include "boot/boot_sect_print_hex.asm"
%include "boot/boot_sect_disk.asm"
%include "boot/32bit-gdt.asm"
%include "boot/32bit-print.asm"
%include "boot/32bit-switch.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print
    call print_nl

    ; Read from disk and store in 0x1000
    mov bx, KERNEL_OFFSET
    mov dh, 16 ; The kernel must fit in however many sectors we load - otherwise we get really weird bugs.
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM: ; The switch should put us here
    mov ebx, MSG_PROT_MODE
    call print_string_pm ; Will be written at the top left corner
    call KERNEL_OFFSET ; Give control to the kernel
    jmp $ ; Stay here when the kernel returns (if ever)

BOOT_DRIVE db 0 ; It is a good idea to stor it in memory because 'dl' may get overwritten
MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

; bootsector
times 510-($-$$) db 0
dw 0xaa55