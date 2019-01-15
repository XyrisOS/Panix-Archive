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
mov bp, 0x8000 ; initialize stack size
mov sp, bp ; reset stack pointers

mov bx, 0x9000 ; es:bx = 0x0000:0x9000 = 0x9000
mov dh, 2 ; read 2 sectors
; Begin disk loading
call disk_load
; Print debug information
mov dx, [0x9000] ; retrieve first loaded word (0xdada)
call print_hex
; New line
call print_nl
; Continue disk loading
mov dx, [0x9000 + 512] ; first word from sector 2 (0xface)
call print_hex
; Freeze
jmp $ ; Jump to current pos

%include "boot_print_hex.asm" 	; include hex print function
%include "boot_print.asm" 	; include print function
%include "boot_sect_disk.asm" 	; include boot sector disk functions

; data
boot_msg:
	; Define our boot message using ASCII
	; and then call this to be printed
	; Important note: 0x0D is the \n char
	db 'Initializing EDIX bootloader...', 0 

; Padding and magic number for BIOS
times 510-($-$$) db 0
; Magic number
dw 0xaa55

; boot sector magic
times 256 dw 0xdada ; sector 2 --> 512 bytes
times 256 dw 0xface ; sector 3 --> 512 bytes
