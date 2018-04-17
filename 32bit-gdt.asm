gdt_start: ; don't remove the labels, they're needed to compute sizes and jumps
    ; the GDT starts with a null 8-bytes
    dd 0x0;
    dd 0x0;

; GDT for code segment. base = 0x00000000, length = 0xffffff
; for flags, refer to os-dev.pdf document, page 36
gdt_code:
    dw 0xffff     ; segment length, bits 0-15
    dw 0x0        ; segment base, bits 0-15
    db 0x0        ; segment base, bits 16-23
    db 10011010b  ; flags (8 bits)
    db 11001111b  ; flags (4 bits) + segment length, bits 16-19
    db 0x0        ; segment base, bits 24-31

; GDT for data segment. Base and length identical to code segment
; some flags changed, again, refer to os-dev.pdf
gdt_data:
    dw 0xffff     ; segment length, bits 0-15
    dw 0x0        ; segment base, bits 0-15
    db 0x0        ; segment base, bits 16-23
    db 10010010b  ; flags (8 bits)
    db 11001111b  ; flags (4 bits) + segment length, bits 16-19
    db 0x0        ; segment base, bits 24-31

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size (16bit), always one less of its true size
    dd gdt_start ; address (32 bit)

; Define some constants for later use
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start