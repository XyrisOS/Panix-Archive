[bits 32]           ; using 32-bit protected mode

VMEM equ 0xb8000    ; VMEM const definition
; colors are defined by 0x(BACK)(FORE)
WHITE_ON_BLACK equ 0x0f

printProtectedMode:
    pusha
    mov edx, VMEM

printProtectedMode_loop:
    mov al, [ebx]           ; [ebx] is the address of our character
    mov ah, WHITE_ON_BLACK  ; [ecx] should store color now ; NORMAL

    cmp al, 0       ; check if end of string
    je printProtectedMode_done

    mov [edx], ax   ; store character + attribute in video memory
    add ebx, 1      ; next char
    add edx, 2      ; next video memory position

    jmp printProtectedMode_loop

printProtectedMode_done:
    popa
    ret
