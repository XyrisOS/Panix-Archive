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
 * File:   interrupts.h
 * Author: Keeton Feavel, Solar Pepper Studios
 * 
 * Created on May 27, 2018, 7:41 PM
 */

#ifndef interrupts_h
#define interrupts_h
#include "types.h"
#include "port.h"
#include "gdt.h"
#include "kprint.h"

class InterruptManager {
protected:

    /**
     * Structure for an Interrupt Descriptor Table entry
     */
    struct GateDescriptor {
        // Class variables
        uint16_t handlerAddressLow; // Lower handler address bits
        uint16_t handlerAddressHigh; // High handler address bits
        uint16_t gdt_codeSegmentSelector; // GDT offset
        uint8_t reserved; // Reserved byte
        uint8_t access; // Access rights

    } __attribute ((packed));

    // Interrupt Descriptor Table (GateDescriptor array of size 256)
    static GateDescriptor interruptDescriptorTable[256];

    /**
     * Pointer structure for the interrupt descriptor table
     */
    struct InterruptDescriptorTablePointer {
        uint16_t size;
        uint32_t base;
    } __attribute ((packed));

    /**
     * Sets an interrupt descriptor table entry
     * @param interruptID - Interrupt number
     * @param codeSegmentSelectorOffset - Offset of the code segment
     * @param privilegeLevel - Interrupt privilege level (executing ring)
     * @param type - Type of interrupt
     * @param handler - Interrupt handler address pointer
     */
    static void setInterruptDescriptorTableEntry(
            uint8_t interruptID,
            uint16_t codeSegmentSelectorOffset,
            uint8_t privilegeLevel,
            uint8_t type,
            void (* handler)()
            );
    
    /* Declare Interrupt Handler Functions */
    static void ignoreInterruptRequest(); // Ignores a given interrupt
    static void handleInterruptRequest0x00(); // Timer interrupt handler
    static void handleInterruptRequest0x01(); // Keyboard interrupt handler
    
    // TODO: Currently only returns the current stack pointer.
    /**
     * Handles interrupts given the interrupt code and the stack pointer
     * @param interruptID - Interrupt number
     * @param esp - Stack pointer
     * @return Returns the given stack pointer.
     */
    static uint32_t handleInterrupt(uint8_t interruptID, uint32_t esp);
    
    // Programmable Interrupt Controller (Master)
    Port_8_Slow picMasterCommand;
    Port_8_Slow picMasterData;
    // Programmable Interrupt Constoller (Slave)
    Port_8_Slow picSlaveCommand;
    Port_8_Slow picSlaveData;
    
public:

    /**
     * Interrupt Manager constructor
     * @param gdt Pointer to the Global Descriptor Table
     */
    InterruptManager(GlobalDescriptorTable * gdt);

    /**
     * Interrupt Manager Destructor
     */
    ~InterruptManager();

    /**
     * Activates interrupt handling.
     */
    void activate();
    
    /**
     * Deactivates interrupt handling.
     */
    void deactivate();
};

#endif /* interrupts_h */

