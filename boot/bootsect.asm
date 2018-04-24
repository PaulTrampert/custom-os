[org 0x7c00] ; bootloader offset
KERNEL_OFFSET equ 0x1000 ; The address used when linking
MEMORY_MAP equ 0x7E00

    mov [BOOT_DRIVE], dl ; BIOS gives us the boot drive in 'dl' on boot
    mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov ax, MEMORY_MAP
    mov [es:di], ax
    call detect_ram
    call load_kernel   ; read the kernel from disk
    call switch_to_pm  ; disable interrupts, load GDT, etc. Finally jumps to BEGIN_PM
    jmp $ ; this should never be called

%include "boot/boot_sect_print.asm"
%include "boot/boot_sect_print_hex.asm"
%include "boot/boot_sect_disk.asm"
%include "boot/32bit-gdt.asm"
%include "boot/32bit-switch.asm"
%include "boot/detect_ram.asm"

[bits 16]
load_kernel:
    ; Read from disk and store in 0x1000
    mov bx, KERNEL_OFFSET
    mov dh, 31 ; The kernel must fit in however many sectors we load - otherwise we get really weird bugs.
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM: ; The switch should put us here
    call KERNEL_OFFSET ; Give control to the kernel
    jmp $ ; Stay here when the kernel returns (if ever)

BOOT_DRIVE db 0 ; It is a good idea to stor it in memory because 'dl' may get overwritten

; bootsector
times 510-($-$$) db 0
dw 0xaa55