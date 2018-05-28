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

.set IRQ_BASE, 0x20

.section .text

# External declaration of InterruptManager::handleInterrupt in interrupts.cpp
.extern _ZN16InterruptManager15handleInterruptEhj

# Handle exceptions
.macro handleException id
.global _ZN16InterruptManager19handleException\id\()Ev
_ZN16InterruptManager19handleException\id\()Ev:
    movb $\id, (interruptID)
    jmp int_bottom
.endm

# Handle interrupts
.macro handleInterruptRequest id
.global _ZN16InterruptManager26handleInterruptRequest\id\()Ev
_ZN16InterruptManager26handleInterruptRequest\id\()Ev:
    movb $\id + IRQ_BASE, (interruptID)
    jmp int_bottom
.endm

handleInterruptRequest 0x00
handleInterruptRequest 0x01

# Jump into InterruptManager::handleInterrupt in interrupts.cpp
int_bottom:
    # Push data onto stack
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interruptID)
    # Call InterruptManager::handleInterrupt in interrupts.cpp
    call _ZN16InterruptManager15handleInterruptEhj
    # Clean stack pointer information
    # addl $5, %esp - Not necessary because contents are overwritten
    movl  %eax, %esp

    # Restore stack values
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

# Ignore interrupts
.global _ZN16InterruptManager22ignoreInterruptRequestEv
_ZN16InterruptManager22ignoreInterruptRequestEv:

    # Finished handling interrupt. Return control to processor.
    iret

.data
    # Initialize interruptID variable
    interruptID: .byte 0
