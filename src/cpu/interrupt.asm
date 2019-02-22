; Defined in isr.c
[extern isrHandler]

; Common ISR code
isrCommonStub:
    ; 1. Save CPU state
	pusha ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov ax, ds ; Lower 16-bits of eax = ds.
	push eax ; save the data segment descriptor
	mov ax, 0x10  ; kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
    ; 2. Call C handler
	call isrHandler
	
    ; 3. Restore state
	pop eax 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8 ; Cleans up the pushed error code and pushed ISR number
	sti
	iret ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
	
; We don't get information about which interrupt was caller
; when the handler is run, so we will need to have a different handler
; for every interrupt.
; Furthermore, some interrupts push an error code onto the stack but others
; don't, so we will push a dummy error code for those which don't, so that
; we have a consistent stack for all of them.

; First make the ISRs global
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; 0: Divide By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp isrCommonStub

; 1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isrCommonStub

; 2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp isrCommonStub

; 3: Int 3 Exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp isrCommonStub

; 4: INTO Exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp isrCommonStub

; 5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp isrCommonStub

; 6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6
    jmp isrCommonStub

; 7: Coprocessor Not Available Exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp isrCommonStub

; 8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push byte 8
    jmp isrCommonStub

; 9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp isrCommonStub

; 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push byte 10
    jmp isrCommonStub

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push byte 11
    jmp isrCommonStub

; 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push byte 12
    jmp isrCommonStub

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push byte 13
    jmp isrCommonStub

; 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push byte 14
    jmp isrCommonStub

; 15: Reserved Exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp isrCommonStub

; 16: Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isrCommonStub

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp isrCommonStub

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isrCommonStub

; 19: Reserved
isr19:
    cli
    push byte 0
    push byte 19
    jmp isrCommonStub

; 20: Reserved
isr20:
    cli
    push byte 0
    push byte 20
    jmp isrCommonStub

; 21: Reserved
isr21:
    cli
    push byte 0
    push byte 21
    jmp isrCommonStub

; 22: Reserved
isr22:
    cli
    push byte 0
    push byte 22
    jmp isrCommonStub

; 23: Reserved
isr23:
    cli
    push byte 0
    push byte 23
    jmp isrCommonStub

; 24: Reserved
isr24:
    cli
    push byte 0
    push byte 24
    jmp isrCommonStub

; 25: Reserved
isr25:
    cli
    push byte 0
    push byte 25
    jmp isrCommonStub

; 26: Reserved
isr26:
    cli
    push byte 0
    push byte 26
    jmp isrCommonStub

; 27: Reserved
isr27:
    cli
    push byte 0
    push byte 27
    jmp isrCommonStub

; 28: Reserved
isr28:
    cli
    push byte 0
    push byte 28
    jmp isrCommonStub

; 29: Reserved
isr29:
    cli
    push byte 0
    push byte 29
    jmp isrCommonStub

; 30: Reserved
isr30:
    cli
    push byte 0
    push byte 30
    jmp isrCommonStub

; 31: Reserved
isr31:
    cli
    push byte 0
    push byte 31
    jmp isrCommonStub