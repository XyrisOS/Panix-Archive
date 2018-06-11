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
# File:   interruptstubs.s
# Author: Keeton Feavel, Solar Pepper Studios
# 
# Created on May 27, 2018
#

# TODO: Update documentation

.set IRQ_BASE, 0x20

.section .text

# External declaration of InterruptManager::handleInterrupt in interrupts.cpp
.extern _ZN16InterruptManager15HandleInterruptEhj

# Handle exceptions
.macro HandleException num
.global _ZN16InterruptManager19HandleException\num\()Ev
_ZN16InterruptManager19HandleException\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm

# Handle interrupts
.macro HandleInterruptRequest num
.global _ZN16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptnumber)
    pushl $0
    jmp int_bottom
.endm


 HandleException 0x00
 HandleException 0x01
 HandleException 0x02
 HandleException 0x03
 HandleException 0x04
 HandleException 0x05
 HandleException 0x06
 HandleException 0x07
 HandleException 0x08
 HandleException 0x09
 HandleException 0x0A
 HandleException 0x0B
 HandleException 0x0C
 HandleException 0x0D
 HandleException 0x0E
 HandleException 0x0F
 HandleException 0x10
 HandleException 0x11
 HandleException 0x12
 HandleException 0x13

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x02
HandleInterruptRequest 0x03
HandleInterruptRequest 0x04
HandleInterruptRequest 0x05
HandleInterruptRequest 0x06
HandleInterruptRequest 0x07
HandleInterruptRequest 0x08
HandleInterruptRequest 0x09
HandleInterruptRequest 0x0A
HandleInterruptRequest 0x0B
HandleInterruptRequest 0x0C
HandleInterruptRequest 0x0D
HandleInterruptRequest 0x0E
HandleInterruptRequest 0x0F
HandleInterruptRequest 0x31

HandleInterruptRequest 0x80

# Jump into InterruptManager::handleInterrupt in interrupts.cpp
int_bottom:
    # Push data onto stack
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    # ring 0 segment register laden
    #cld
    #mov $0x10, %eax
    #mov %eax, %eds
    #mov %eax, %ees

    pushl %esp
    push (interruptnumber)
    # Call InterruptManager::handleInterrupt in interrupts.cpp
    call _ZN16InterruptManager15HandleInterruptEhj
    # Clean stack pointer information
    # add %esp, 6
    mov %eax, %esp

    # Restore stack values
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa

    # Ignore interrupts
    .global _ZN16InterruptManager15InterruptIgnoreEv
    _ZN16InterruptManager15InterruptIgnoreEv:
    
    # Finished handling interrupt. Return control to processor.
    iret

.data
    # Initialize interruptID variable
    interruptnumber: .byte 0
