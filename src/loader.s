# Set GRUB Bootloader magic number, flags, and checksum
.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

# Declare the multiboot information
.section .mulitboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

# Load the external functions for calling the compiled C++ kernel
.section .text
.extern kernelMain
.extern callConstructors
.global loader

# Set the kernel stack and initialize registers
loader:
    mov $kernel_stack, %esp
    call callConstructors
    push %eax
    push %ebx
    call kernelMain

# Ensure the kernel does not exit by disabling interupts and halting the CPU
_stop:
    cli
    hlt
    jmp _stop

# Allocate extra space for the kernel stack
.section .bss
.space 2*1024*1024 # 2 MB
kernel_stack:
