#
# Copyright (C) 2018 Keeton Feavel, Solar Pepper Studios
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) anyf later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#

#
# File:   loader.s
# Author: Keeton Feavel, Solar Pepper Studios
# 
# Created on May 24, 2018
#

# Set GRUB Bootloader magic number, flags, and checksum
.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

# Declare the multiboot information
.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

# Load the external functions for calling the compiled C++ kernel
.section .text
.extern kernel
.extern callConstructors
.global loader

# Set the kernel stack and initialize registers
loader:
    mov $kernel_stack, %esp
    call callConstructors
    push %eax
    push %ebx
    call kernel

# Ensure the kernel does not exit by disabling interupts and halting the CPU
_stop:
    cli
    hlt
    jmp _stop

# Allocate extra space for the kernel stack
.section .bss
.space 2*1024*1024 # 2 MB
kernel_stack:
