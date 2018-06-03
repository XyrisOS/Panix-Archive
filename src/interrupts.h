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

#include "gdt.h"
#include "types.h"
#include "port.h"
#include "kprint.h"

class InterruptManager {
protected:

    /**
     * Structure for an Interrupt Descriptor Table entry
     */
    struct GateDescriptor {
        uint16_t handlerAddressLowBits;
        uint16_t gdt_codeSegmentSelector;
        uint8_t reserved;
        uint8_t access;
        uint16_t handlerAddressHighBits;
    } __attribute__ ((packed));

    // Interrupt Descriptor Table (GateDescriptor array of size 256)
    static GateDescriptor interruptDescriptorTable[256];

    /**
     * Pointer structure for the interrupt descriptor table
     */
    struct InterruptDescriptorTablePointer {
        uint16_t size;
        uint32_t base;
    } __attribute__ ((packed));

    // Offset for hardware interrupts (in interruptstubs.s)
    uint16_t hardwareInterruptOffset;
    
    // TODO: Needs updated documentation
    /**
     * Sets an interrupt descriptor table entry
     * @param interruptID - Interrupt number
     * @param codeSegmentSelectorOffset - Offset of the code segment
     * @param privilegeLevel - Interrupt privilege level (executing ring)
     * @param type - Type of interrupt
     * @param handler - Interrupt handler address pointer
     */
    static void SetInterruptDescriptorTableEntry(uint8_t interrupt,
            uint16_t codeSegmentSelectorOffset, void (*handler)(),
            uint8_t DescriptorPrivilegeLevel, uint8_t DescriptorType);

    /* Declare Interrupt Handler Functions */
    static void InterruptIgnore();              // Ignores a given interrupt
    static void HandleInterruptRequest0x00();   // Timer interrupt handler
    static void HandleInterruptRequest0x01();   // Keyboard interrupt handler
    static void HandleInterruptRequest0x02();
    static void HandleInterruptRequest0x03();
    static void HandleInterruptRequest0x04();
    static void HandleInterruptRequest0x05();
    static void HandleInterruptRequest0x06();
    static void HandleInterruptRequest0x07();
    static void HandleInterruptRequest0x08();
    static void HandleInterruptRequest0x09();
    static void HandleInterruptRequest0x0A();
    static void HandleInterruptRequest0x0B();
    static void HandleInterruptRequest0x0C();
    static void HandleInterruptRequest0x0D();
    static void HandleInterruptRequest0x0E();
    static void HandleInterruptRequest0x0F();
    static void HandleInterruptRequest0x31();

    /* Declare Exception Handler Functions */
//    static void HandleException0x00();
//    static void HandleException0x01();
//    static void HandleException0x02();
//    static void HandleException0x03();
//    static void HandleException0x04();
//    static void HandleException0x05();
//    static void HandleException0x06();
//    static void HandleException0x07();
//    static void HandleException0x08();
//    static void HandleException0x09();
//    static void HandleException0x0A();
//    static void HandleException0x0B();
//    static void HandleException0x0C();
//    static void HandleException0x0D();
//    static void HandleException0x0E();
//    static void HandleException0x0F();
//    static void HandleException0x10();
//    static void HandleException0x11();
//    static void HandleException0x12();
//    static void HandleException0x13();

    // TODO: Currently only returns the current stack pointer.
    /**
     * Handles interrupts given the interrupt code and the stack pointer
     * @param interruptID - Interrupt number
     * @param esp - Stack pointer
     * @return Returns the given stack pointer.
     */
    static uint32_t HandleInterrupt(uint8_t interrupt, uint32_t esp);

    /**
     * 
     * @param interrupt
     * @param esp
     * @return 
     */
    uint32_t HandleInterruptAction(uint8_t interrupt, uint32_t esp);
    
    // Programmable Interrupt Controller (Master)
    Port_8_Slow PICMasterCommandPort;
    Port_8_Slow PICMasterDataPort;
    // Programmable Interrupt Constoller (Slave)
    Port_8_Slow PICSlaveCommandPort;
    Port_8_Slow PICSlaveDataPort;
    
    // Pointer to the active interrupt manager
    static InterruptManager * ActiveInterruptManager;

public:
    /**
     * Interrupt Manager constructor
     * @param hardwareInterruptOffset Interrupt offset to differentiate between CPU and code
     * @param globalDescriptorTable Pointer to the Global Descriptor Table
     */
    InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable * globalDescriptorTable);
    
    /**
     * Interrupt Manager Destructor
     */
    ~InterruptManager();
    
    /**
     * Offset for the hardware to differentiate betten CPU and code interrupts
     * @return Returns the hardware offset
     */
    uint16_t HardwareInterruptOffset();
    
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