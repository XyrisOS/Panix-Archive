/* 
 * File:   interrupts.cpp
 * Author: Keeton Feavel, Solar Pepper Studios
 * 
 * Created on May 27, 2018, 7:41 PM
 */
#include "interruptmanager.h"

// Initialize class variables
InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];
InterruptManager * InterruptManager::ActiveInterruptManager = 0;

#pragma mark InteruptHandler

InterruptHandler::InterruptHandler(uint8_t num, InterruptManager* mgr) {
    // Set the interrupt and active manager variables
    interruptNumber = num;
    manager = mgr;
    // Insert self into manager's handler array at the index of the interrupt ID
    manager->handlers[interruptNumber] = this;
    kprint_status(true, "InterruptHandler");
}

InterruptHandler::~InterruptHandler() {
    if (manager->handlers[interruptNumber] == this) {
        manager->handlers[interruptNumber] = 0;
    }
}

uint32_t InterruptHandler::HandleInterrupt(uint32_t esp) {
    // TODO: Update interrupt handler.
    return esp;
}

#pragma mark InterruptManager

InterruptManager::InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* globalDescriptorTable) :
PICMasterCommandPort(0x20), PICMasterDataPort(0x21),
PICSlaveCommandPort(0xA0), PICSlaveDataPort(0xA1) {
    this->hardwareInterruptOffset = hardwareInterruptOffset;
    uint32_t CodeSegment = globalDescriptorTable->CodeSegmentSelector();

    const uint8_t IDT_INTERRUPT_GATE = 0xE;
    for (uint8_t i = 255; i > 0; --i) {
        handlers[i] = 0;
        SetInterruptDescriptorTableEntry(i, CodeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);
    }
    SetInterruptDescriptorTableEntry(0, CodeSegment, &InterruptIgnore, 0, IDT_INTERRUPT_GATE);

//    SetInterruptDescriptorTableEntry(0x00, CodeSegment, &HandleException0x00, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x01, CodeSegment, &HandleException0x01, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x02, CodeSegment, &HandleException0x02, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x03, CodeSegment, &HandleException0x03, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x04, CodeSegment, &HandleException0x04, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x05, CodeSegment, &HandleException0x05, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x06, CodeSegment, &HandleException0x06, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x07, CodeSegment, &HandleException0x07, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x08, CodeSegment, &HandleException0x08, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x09, CodeSegment, &HandleException0x09, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x0A, CodeSegment, &HandleException0x0A, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x0B, CodeSegment, &HandleException0x0B, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x0C, CodeSegment, &HandleException0x0C, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x0D, CodeSegment, &HandleException0x0D, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x0E, CodeSegment, &HandleException0x0E, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x0F, CodeSegment, &HandleException0x0F, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x10, CodeSegment, &HandleException0x10, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x11, CodeSegment, &HandleException0x11, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x12, CodeSegment, &HandleException0x12, 0, IDT_INTERRUPT_GATE);
//    SetInterruptDescriptorTableEntry(0x13, CodeSegment, &HandleException0x13, 0, IDT_INTERRUPT_GATE);

    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x00, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x01, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x02, CodeSegment, &HandleInterruptRequest0x02, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x03, CodeSegment, &HandleInterruptRequest0x03, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x04, CodeSegment, &HandleInterruptRequest0x04, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x05, CodeSegment, &HandleInterruptRequest0x05, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x06, CodeSegment, &HandleInterruptRequest0x06, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x07, CodeSegment, &HandleInterruptRequest0x07, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x08, CodeSegment, &HandleInterruptRequest0x08, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x09, CodeSegment, &HandleInterruptRequest0x09, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0A, CodeSegment, &HandleInterruptRequest0x0A, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0B, CodeSegment, &HandleInterruptRequest0x0B, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0C, CodeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0D, CodeSegment, &HandleInterruptRequest0x0D, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0E, CodeSegment, &HandleInterruptRequest0x0E, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0F, CodeSegment, &HandleInterruptRequest0x0F, 0, IDT_INTERRUPT_GATE);

    // Communicate with Programmable Interrupt Controller
    PICMasterCommandPort.write(0x11);
    PICSlaveCommandPort.write(0x11);
    // Tell Master PIC to add 0x20 to any received interrupts
    PICMasterDataPort.write(hardwareInterruptOffset);
    // Tell Slave PIC to add 0x28 to any received interrupts
    PICSlaveDataPort.write(hardwareInterruptOffset + 8);
    // Write Master and Slave roles to each PIC
    PICMasterDataPort.write(0x04); // Master Mode
    PICSlaveDataPort.write(0x02); // Slave Mode
    // ???
    PICMasterDataPort.write(0x01);
    PICSlaveDataPort.write(0x01);
    // ???
    PICMasterDataPort.write(0x00);
    PICSlaveDataPort.write(0x00);

    // Tell the processor to use the constructed IDT
    InterruptDescriptorTablePointer idt_pointer;
    idt_pointer.size = 256 * sizeof (GateDescriptor) - 1;
    idt_pointer.base = (uint32_t) interruptDescriptorTable;

    // Load the IDT by calling the lidt assembly instruction
    asm volatile("lidt %0" : : "m" (idt_pointer));
    
    kprint_status(true, "InterruptManager");
}

void InterruptManager::SetInterruptDescriptorTableEntry(
        uint8_t interrupt,
        uint16_t segmentSelectorOffset, 
        void (*handler)(), 
        uint8_t privilegeLevel, 
        uint8_t type) {
    // address of pointer to code segment (relative to global descriptor table)
    // and address of the handler (relative to segment)
    interruptDescriptorTable[interrupt].handlerAddressLowBits = ((uint32_t) handler) & 0xFFFF;
    interruptDescriptorTable[interrupt].handlerAddressHighBits = (((uint32_t) handler) >> 16) & 0xFFFF;
    interruptDescriptorTable[interrupt].gdt_codeSegmentSelector = segmentSelectorOffset;

    const uint8_t IDT_DESC_PRESENT = 0x80;
    const uint8_t access = IDT_DESC_PRESENT | ((privilegeLevel & 3) << 5) | type;
    interruptDescriptorTable[interrupt].access = access;
    interruptDescriptorTable[interrupt].reserved = 0;
}

InterruptManager::~InterruptManager() {
    deactivate();
}

uint16_t InterruptManager::HardwareInterruptOffset() {
    return hardwareInterruptOffset;
}

void InterruptManager::activate() {
    if(ActiveInterruptManager == 0)
    {
        ActiveInterruptManager = this;
        kprint_status(true, "InterruptManager::activate()");
        asm("sti");
    } else {
        // If there is another interrupt manager, deactivate the active
        ActiveInterruptManager->deactivate();
        ActiveInterruptManager = this;
        kprint_status(false, "InterruptManager::activate() Already active!");
    }
}

void InterruptManager::deactivate() {
    // If there this is the active interrupt manager, deactivate
    if (ActiveInterruptManager == this)
    {
        ActiveInterruptManager = 0;
        asm("cli");
        kprint_status(true, "InterruptManager::deactivate()");
    }
}

uint32_t InterruptManager::HandleInterrupt(uint8_t interrupt, uint32_t esp) {
    // Check if there is a interrupt manager
    if (ActiveInterruptManager != 0) {
        ActiveInterruptManager->HandleInterruptAction(interrupt, esp);
    } else {
        // Create interrupt manager?
    }
    // Return the esp (stack?)
    return esp;
}

uint32_t InterruptManager::HandleInterruptAction(uint8_t interrupt, uint32_t esp) {
    // If a handler for this interrupt exists
    if (handlers[interrupt] != 0) {
        // Call handle interrupt method
        esp = handlers[interrupt]->HandleInterrupt(esp);
    }
    else
    // If the interrupt is not the timer interrupt, print
    if (interrupt != hardwareInterruptOffset) {
        // Set interrupt message char array
        char foo [] = "INTERRUPT 0x00 NOT HANDLED\n";
        char hex [] = "0123456789ABCDEF";
        // Print interrupt message as an error
        foo[12] = hex[(interrupt >> 4) & 0xF];
        foo[13] = hex[interrupt & 0xF];
        kprint_error(foo);
    }
    // If the hardware interrupt offset is between 0x20 and 0x30
    if ((hardwareInterruptOffset <= interrupt) && (interrupt < hardwareInterruptOffset + 16)) {
        // Send reply message to the hardware
        PICMasterCommandPort.write(0x20); // Master PIC answer
        // If the interrupt is between 0x28 and 0x30, send message to slave PIC
        if (hardwareInterruptOffset + 8 <= interrupt) {
            PICSlaveCommandPort.write(0x20);
        }
    }
    // Return the esp (stack?)
    return esp;
}