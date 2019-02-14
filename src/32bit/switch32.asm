[bits 16]
switch_32:
    cli 				                ; disable interrupts
    lgdt [gdt_descriptor]               ; load the GDT descriptor
    mov eax, cr0			            ; move control bit 0 into eax
    or eax, 0x1 			            ; set 32-bit mode bit in cr0
    mov cr0, eax			            ; load eax into control bit 0
    jmp CODE_SEG:init_protected_mode 	; far jump by using a different segment

[bits 32]
init_protected_mode: 			; 32 bit protected mode is now initialized
    mov ax, DATA_SEG 			; update segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 			; update the stack right at the top of the free space
    mov esp, ebp

    call protected_mode_init 	; call the initialization function in the main boot sect file
