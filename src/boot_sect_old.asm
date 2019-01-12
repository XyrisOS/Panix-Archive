mov ah, 0x0e ; scrolling tty mode
mov al, 'B'
int 0x10
mov al, 'o'
int 0x10
int 0x10
mov al, 't'
int 0x10
mov al, 'i'
int 0x10
mov al, 'n'
int 0x10
mov al, 'g'
int 0x10
mov al, ' '
int 0x10
mov al, 'E'
int 0x10
mov al, 'D'
int 0x10
mov al, 'I'
int 0x10
mov al, 'X'
int 0x10
mov al, '.'
int 0x10
int 0x10
int 0x10

jmp $ ; Jump to current loop

; Padding and magic number for BIOS
times 510-($-$$) db 0
; Magic number
dw 0xaa55 
