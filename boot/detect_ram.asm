; Use the INT 0x15, eax=DETECT_MEM_FUNC BIOS function to get a memory map
; Inputs: es:di -> destination buffer for 24 byte entries. the first 16-bits will be the count
; outputs: ENTRY_COUNT
[bits 16]
detect_ram:
  pusha
  xor bp, bp
  xor ebx, ebx
  mov edx, MAGIC_NUM
  mov eax, DETECT_MEM_FUNC
  mov ecx, ENTRY_SIZE
  mov [es:di + 20], dword 1 ; force valid ACPI 3.x entry
  int 0x15
  jc short .failed
  mov edx, MAGIC_NUM
  cmp eax, edx
  jne short .failed
  test ebx, ebx
  je short .failed

.detect_ram_loop:
  mov eax, DETECT_MEM_FUNC
  mov [es:di + 20], dword 1
  mov ecx, 24
  int 0x15
  jc short .done
  mov edx, MAGIC_NUM

.check_entry:
  jcxz .skip_entry
  cmp cl, 20
  jbe short .not_extended
  test byte [es:di + 20], 1
  je short .skip_entry

.not_extended:
  mov ecx, [es:di + 8]
  or ecx, [es:di + 12]
  jz .skip_entry
  inc bp
  add di, 24

.skip_entry:
  test ebx, ebx
  jne short .detect_ram_loop

.done:
  mov [MMAP_ENTRY_COUNT], bp
  popa
  ret

.failed:
  stc
  hlt

MAGIC_NUM equ 0x534D4150
DETECT_MEM_FUNC equ 0x0000E820
ENTRY_SIZE equ 24
MMAP_ENTRY_COUNT dw 0