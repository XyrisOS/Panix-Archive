; Define boot sector variable offset
[org 0x7c00]
; enables scrolling tty mode
mov ah, 0x0e
; Move message into array source register
; Required by the print function included below
mov bx, boot_msg
call print
call print_nl
; Begin stack initialization
mov bp, 0x9000 	; initialize stack size
mov sp, bp 	; reset stack pointers
; Print 16 bit real mode message
mov bx, real_msg
call print
call print_nl
; Call 32 bit switch functions
call switch_32
jmp $ ; Failsafe in event switch fails

; mov bx, 0x9000 ; es:bx = 0x0000:0x9000 = 0x9000
; mov dh, 2 ; read 2 sectors
; Begin disk loading
; call disk_load
; Print debug information
; mov dx, [0x9000] ; retrieve first loaded word (0xdada)
; call print_hex
; New line
; call print_nl
; Continue disk loading
; mov dx, [0x9000 + 512] ; first word from sector 2 (0xface)
; call print_hex
; Freeze
; jmp $ ; Jump to current pos

; -- include all required 16 bit files --
%include "boot_print_hex.asm" 	; include hex print function
%include "boot_print.asm" 	; include print function
%include "boot_sect_disk.asm" 	; include boot sector disk functions
; -- include all required 32 bit files --
%include "../32bit/switch32.asm"; include 32 bit protected mode functions
%include "../32bit/color32.asm"	; include 32 bit print colors
%include "../32bit/print32.asm" ; include 32 bit print functions
%include "../32bit/gdt32.asm"   ; include 32 bit GDT functions

; Begin 32 bit instructions
[bits 32]
protected_mode_init:
	mov ebx, prot_msg 	; Move the message into the appropriate register
	; mov ecx, 0xF0		; Move normal color into ecx for usage
	call print32 		; Call the protected mode print function
	jmp $			; Stay where you are criminal scum!

; data
boot_msg:
	; Define our boot message using ASCII
	; and then call this to be printed
	; Important note: 0x0D is the \n char
	db 'Initializing EDIX bootloader...', 0 

real_msg:
	db 'Working in 16 bit real mode...', 0

prot_msg:
	db 'Working in 32 bit protected mode...', 0

; Padding and magic number for BIOS
times 510-($-$$) db 0
; Magic number
dw 0xaa55

; boot sector magic
times 256 dw 0xdada ; sector 2 --> 512 bytes
times 256 dw 0xface ; sector 3 --> 512 bytes
