mov ah, 0x0e ; tty mode

mov bp, 0x8000 ; an address far from 0x7c00 so as not to be overwritten
mov sp, bp ; empty stack init

push 'A'
push 'B'
push 'C'

; to show how the stack grows downwards
mov al, [0x7ffe] ; 0x8000 - 2
int 0x10

; can't access 0x8000 now because you can only access the top of the stack
mov al, [0x8000]
int 0x10

; recover characters using standard proc: 'pop'
; Can only pop full words so we need an axiliary register to manipulate

pop bx
mov al, bl
int 0x10 ; print C

pop bx
mov al, bl
int 0x10 ; print B

pop bx
mov al, bl
int 0x10 ; print A

; Stack data is now garbage
mov al, [0x8000]
int 0x10

jmp $
times 510-($-$$) db 0
dw 0xaa55
