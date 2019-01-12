; Define boot sector variable offset
[org 0x7c00]
; enables scrolling tty mode
mov ah, 0x0e
; Move message into array source register
; Required by the print function included below
mov si, boot_msg
call print
;print:
;	mov ah, 0Eh
;.printloop:
;	lodsb
;	cmp al, 0x0D 	; Make sure we haven't hit the nl terminator
;	je .printdone	; jump to done if nl
;	int 10h		; print to the tty if not nl
;	jmp .printloop 	; jump back to loop and continue printing
;
;.printdone:
;	jmp $ ; Jump to current loop

jmp $ ; Jump to current pos

%include "boot_print.asm" ; include print function

; data
boot_msg:
	; Define our boot message using ASCII
	; and then call this to be printed
	; Important note: 0x0D is the \n char
	db 'Initializing EDIX bootloader...', 0x0D 

; Padding and magic number for BIOS
times 510-($-$$) db 0
; Magic number
dw 0xaa55
