/*
 * Copyright (C) 2018 Keeton Feavel, Solar Pepper Studios
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/* 
 * File:   interrupts.cpp
 * Author: Keeton Feavel, Solar Pepper Studios
 * 
 * Created on May 27, 2018, 7:48 PM
 */

#include "interrupts.h"

// Get class variables
InterruptManager::GateDescriptor
InterruptManager::interruptDescriptorTable[256];

InterruptManager::InterruptManager(GlobalDescriptorTable * gdt) :
picMasterCommand(0x20), picMasterData(0x21),
picSlaveCommand(0xA0), picSlaveData(0xA1) {
    // Get values
    uint16_t codeSegment = gdt->CodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;
    // Initialize the IDT
    for (uint16_t i = 0; i < 256; i++) {
        setInterruptDescriptorTableEntry(
                i, // Index / interrupt ID
                codeSegment, // Code segment selector
                0, // Kernel mode
                IDT_INTERRUPT_GATE, // Type of interrupt
                &ignoreInterruptRequest // Ignore interrupt function
                );
    }
    // Indexes start at 0x20 because they are increased
    // by IRQ_BASE in interruptstubs.s (Hardware Interrupt Offset)
    // Handle interrupt 0x00
    setInterruptDescriptorTableEntry(
            0x20,
            codeSegment,
            0,
            IDT_INTERRUPT_GATE,
            &handleInterruptRequest0x00
            );
    // Handle interrupt 0x01
    setInterruptDescriptorTableEntry(
            0x21,
            codeSegment,
            0,
            IDT_INTERRUPT_GATE,
            &handleInterruptRequest0x01
            );
    
    // Communicate with Programmable Interrupt Controller
    picMasterCommand.write(0x11);
    picSlaveCommand.write(0x11);
    // Tell Master PIC to add 0x20 to any received interrupts
    picMasterData.write(0x20);
    // Tell Slave PIC to add 0x28 to any received interrupts
    picSlaveData.write(0x28);
    // Write Master and Slave roles to each PIC
    picMasterData.write(0x04); // Master mode
    picSlaveData.write(0x02);  // Slave mode
    
    picMasterData.write(0x01);
    picSlaveData.write(0x01);
    
    picMasterData.write(0x00);
    picSlaveData.write(0x00);
    
    // Tell the processor to use the constructed IDT
    InterruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof (GateDescriptor) - 1;
    idt.base = (uint32_t) interruptDescriptorTable;

    // Load the IDT by calling the lidt assembly instruction
    asm volatile("lidt %0" : : "m" (idt));

}

InterruptManager::~InterruptManager() {

}

void InterruptManager::setInterruptDescriptorTableEntry (
        uint8_t interruptID,
        uint16_t codeSegmentSelectorOffset,
        uint8_t privilegeLevel,
        uint8_t type,
        void (* handler)()) {
    // Get values
    const uint8_t IDT_DESC_PRESENT = 0x80;
    const uint8_t access = IDT_DESC_PRESENT | ((privilegeLevel & 3) << 5) | type;
    // Set each entry
    interruptDescriptorTable[interruptID].handlerAddressLow = (((uint32_t) handler) & 0xFFFF);
    interruptDescriptorTable[interruptID].handlerAddressHigh = ((((uint32_t) handler) >> 16)& 0xFFFF);
    interruptDescriptorTable[interruptID].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
    interruptDescriptorTable[interruptID].reserved = 0;
    interruptDescriptorTable[interruptID].access = access;
}

void InterruptManager::Activate() {
    // Call the "start interrupts" assembly command
    asm volatile("sti");
}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptID, uint32_t esp) {
    // Print an interrupt status to the terminal
    kprint_error("[ INTERRUPT ]\n");

    return esp;
}