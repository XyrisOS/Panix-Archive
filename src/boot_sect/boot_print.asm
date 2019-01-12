; This function assumes the string will be in register si
print:
        mov ah, 0Eh
.printloop:
        lodsb
        cmp al, 0x0D    ; Make sure we haven't hit the nl terminator
        je .printdone   ; jump to done if nl
        int 10h         ; print to the tty if not nl
        jmp .printloop  ; jump back to loop and continue printing

.printdone:
        ret ; Return
