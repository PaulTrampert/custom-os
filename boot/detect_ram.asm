; Use the INT 0x15, eax=0xE820 BIOS function to get a memory map
; Inputs: es:di -> destination buffer for 24 byte entries
; outputs: bp = entry count, trashes all registers except esi
detect_ram:
  mov bx, MSG_DETECTING_RAM
  call print
  xor ebx, ebx  ; ebx must be 0 to start
  xor bp, bp    ; keep an entry count in bp
  mov edx, MAGIC_NUM ; Place "SMAP" into edx
  mov eax, DETECT_MEM_FUNC
  mov [es:di + 20], dword 1 ; force a valid ACPI 3.x entry
  mov ecx, 24   ; ask for 24 bytes
  int 0x15
  jc ram_error  ; Carry set on first call means "unsupported"
  popa
  ret

ram_error:
  mov bx, MSG_RAM_ERROR
  call print
  hlt

MAGIC_NUM equ 0x534D4150
DETECT_MEM_FUNC equ 0x0000E820
ENTRY_SIZE equ 24
MSG_RAM_ERROR db "Error detecting ram", 0
MSG_DETECTING_RAM db "Detecting ram...", 0