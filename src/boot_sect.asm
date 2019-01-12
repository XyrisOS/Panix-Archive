; Define boot sector variable offset
[org 0x7c00]
; enables scrolling tty mode
mov ah, 0x0e
; Print out message
mov si, boot_msg
; Have to loop through the length of our message
; Since calling 'int 0x10' only prints 1 char
call print
print:
	mov ah, 0Eh
.printloop:
	lodsb
	cmp al, 0x00 	; Make sure we haven't hit the NULL terminator
	je .printdone	; jump to done if NULL
	int 10h		; print to the tty if not NULL
	jmp .printloop 	; jump back to loop and continue printing

.printdone:
	jmp $ ; Jump to current loop

boot_msg:
	; Define our boot message using ASCII
	; and then call this to be printed
	db 'Booting EDIX Kernel...', 0x00 

; Padding and magic number for BIOS
times 510-($-$$) db 0
; Magic number
dw 0xaa55
