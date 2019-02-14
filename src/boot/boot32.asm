; -- include all required 16 bit files --
%include "boot_print.asm"       ; include print function
%include "boot_print_hex.asm"   ; include hex print function
%include "boot_sect_disk.asm"     ; include boot sector disk functions
; -- include all required 32 bit files --
%include "../32bit/switch32.asm"; include 32 bit protected mode functions
%include "../32bit/color32.asm"    ; include 32 bit print colors
%include "../32bit/print32.asm" ; include 32 bit print functions
%include "../32bit/gdt32.asm"   ; include 32 bit GDT functions

; Define boot sector variable offset
[org 0x7c00]
KERNEL_OFFSET equ 0x1000

    mov [BOOT_DRIVE], dl    ; Set the BIOS boot drive
    ; Begin stack initialization
    mov bp, 0x9000          ; initialize stack size
    mov sp, bp              ; reset stack pointers

    ; Move message into array source register
    ; Required by the print function included below
    mov bx, boot_msg
    call print
    call print_nl

    ; Print 16 bit real mode message
    ; Let the user know 16 bit mode is enabled
    mov bx, real_msg
    call print
    call print_nl

    ; Call 32 bit switch functions
    call load_kernel        ; Load the kernel into memory
    call switch_32          ; Switch into 32 bit protected mode
    jmp $                   ; Failsafe in event switch fails

[bits 16]
load_kernel:
    mov bx, kernel_msg
    call print
    call print_nl

    mov bx, KERNEL_OFFSET   ; Read off of disk and into memory at 0x1000
    mov dh, 2
    mov dl, [BOOT_DRIVE]    ; Move BOOT_DRIVE contents in DL
    call disk_load
    ret

; Begin 32 bit instructions
[bits 32]
protected_mode_init:
	mov ebx, prot_msg 	    ; Move the message into the appropriate register
	call print32 		    ; Call the protected mode print function
    call KERNEL_OFFSET      ; Jump into the PANIX kernel
	jmp $			        ; Stay where you are criminal scum!

; data
; Store in memory as dl register is volitile
BOOT_DRIVE db 0
; Define our boot message using ASCII
; and then call this to be printed
; Important note: 0x0 is the \n char
boot_msg db 'Initializing PANIX bootloader...', 0
real_msg db 'Working in 16 bit real mode...', 0
prot_msg db 'Working in 32 bit protected mode...', 0
kernel_msg db 'Loading PANIX kernel...', 0

; Padding and magic number for BIOS
times 510-($-$$) db 0
dw 0xaa55
