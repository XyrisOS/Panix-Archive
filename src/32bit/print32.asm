[bits 32]           ; using 32-bit protected mode

VMEM equ 0xb8000    ; VMEM const definition
; colors are defined by 0x(BACK)(FORE)
; WHITE_ON_BLACK equ 0x0f

print32:
    pusha
    mov edx, VMEM

print32_loop:
    mov al, [ebx]   ; [ebx] is the address of our character
    mov ah, NORMAL  ; [ecx] should store color now ; NORMAL

    cmp al, 0       ; check if end of string
    je print32_done

    mov [edx], ax   ; store character + attribute in video memory
    add ebx, 1      ; next char
    add edx, 2      ; next video memory position

    jmp print32_loop

print32_done:
    popa
    ret