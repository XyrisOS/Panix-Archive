#include <cpu/interrupts/InterruptManager.hpp>

void kprint(const char* str);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];
InterruptManager* InterruptManager::activeInterruptManager = nullptr;

void InterruptManager::setInterruptDescriptorTableEntry(uint8_t interrupt,
    uint16_t CodeSegment, void (*handler)(), uint8_t DescriptorPrivilegeLevel, uint8_t DescriptorType)
{
    // address of pointer to code segment (relative to global descriptor table)
    // and address of the handler (relative to segment)
    interruptDescriptorTable[interrupt].handlerAddressLowBits = ((uint32_t) handler) & 0xFFFF;
    interruptDescriptorTable[interrupt].handlerAddressHighBits = (((uint32_t) handler) >> 16) & 0xFFFF;
    interruptDescriptorTable[interrupt].gdt_codeSegmentSelector = CodeSegment;

    const uint8_t IDT_DESC_PRESENT = 0x80;
    interruptDescriptorTable[interrupt].access = IDT_DESC_PRESENT | ((DescriptorPrivilegeLevel & 3) << 5) | DescriptorType;
    interruptDescriptorTable[interrupt].reserved = 0;
}


InterruptManager::InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* globalDescriptorTable)
    : programmableInterruptControllerMasterCommandPort(0x20),
      programmableInterruptControllerMasterDataPort(0x21),
      programmableInterruptControllerSlaveCommandPort(0xA0),
      programmableInterruptControllerSlaveDataPort(0xA1)
{
    this->hardwareInterruptOffset = hardwareInterruptOffset;
    uint32_t CodeSegment = globalDescriptorTable->CodeSegmentSelector();

    const uint8_t IDT_INTERRUPT_GATE = 0xE;
    for(uint8_t i = 255; i > 0; --i)
    {
        setInterruptDescriptorTableEntry(i, CodeSegment, &interruptIgnore, 0, IDT_INTERRUPT_GATE);
    }
    setInterruptDescriptorTableEntry(0, CodeSegment, &interruptIgnore, 0, IDT_INTERRUPT_GATE);

    setInterruptDescriptorTableEntry(0x00, CodeSegment, &handleException0x00, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x01, CodeSegment, &handleException0x01, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x02, CodeSegment, &handleException0x02, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x03, CodeSegment, &handleException0x03, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x04, CodeSegment, &handleException0x04, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x05, CodeSegment, &handleException0x05, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x06, CodeSegment, &handleException0x06, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x07, CodeSegment, &handleException0x07, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x08, CodeSegment, &handleException0x08, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x09, CodeSegment, &handleException0x09, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0A, CodeSegment, &handleException0x0A, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0B, CodeSegment, &handleException0x0B, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0C, CodeSegment, &handleException0x0C, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0D, CodeSegment, &handleException0x0D, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0E, CodeSegment, &handleException0x0E, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x0F, CodeSegment, &handleException0x0F, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x10, CodeSegment, &handleException0x10, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x11, CodeSegment, &handleException0x11, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x12, CodeSegment, &handleException0x12, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(0x13, CodeSegment, &handleException0x13, 0, IDT_INTERRUPT_GATE);

    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x00, CodeSegment, &handleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x01, CodeSegment, &handleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x02, CodeSegment, &handleInterruptRequest0x02, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x03, CodeSegment, &handleInterruptRequest0x03, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x04, CodeSegment, &handleInterruptRequest0x04, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x05, CodeSegment, &handleInterruptRequest0x05, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x06, CodeSegment, &handleInterruptRequest0x06, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x07, CodeSegment, &handleInterruptRequest0x07, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x08, CodeSegment, &handleInterruptRequest0x08, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x09, CodeSegment, &handleInterruptRequest0x09, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0A, CodeSegment, &handleInterruptRequest0x0A, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0B, CodeSegment, &handleInterruptRequest0x0B, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0C, CodeSegment, &handleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0D, CodeSegment, &handleInterruptRequest0x0D, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0E, CodeSegment, &handleInterruptRequest0x0E, 0, IDT_INTERRUPT_GATE);
    setInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0F, CodeSegment, &handleInterruptRequest0x0F, 0, IDT_INTERRUPT_GATE);

    programmableInterruptControllerMasterCommandPort.write(0x11);
    programmableInterruptControllerSlaveCommandPort.write(0x11);

    // remap
    programmableInterruptControllerMasterDataPort.write(hardwareInterruptOffset);
    programmableInterruptControllerSlaveDataPort.write(hardwareInterruptOffset + 8);

    programmableInterruptControllerMasterDataPort.write(0x04);
    programmableInterruptControllerSlaveDataPort.write(0x02);

    programmableInterruptControllerMasterDataPort.write(0x01);
    programmableInterruptControllerSlaveDataPort.write(0x01);

    programmableInterruptControllerMasterDataPort.write(0x00);
    programmableInterruptControllerSlaveDataPort.write(0x00);

    InterruptDescriptorTablePointer idt_pointer;
    idt_pointer.size  = 256 * sizeof(GateDescriptor) - 1;
    idt_pointer.base  = (uint32_t)interruptDescriptorTable;
    asm volatile("lidt %0" : : "m" (idt_pointer));
}

InterruptManager::~InterruptManager()
{
    deactivate();
}

uint16_t InterruptManager::getHardwareInterruptOffset()
{
    return hardwareInterruptOffset;
}

void InterruptManager::activate()
{
    if(activeInterruptManager == nullptr)
    {
        activeInterruptManager = this;
        asm("sti");
    }
}

void InterruptManager::deactivate()
{
    if (activeInterruptManager == this)
    {
        activeInterruptManager = nullptr;
        
        asm("cli");
        
    }
}

uint32_t InterruptManager::handleInterrupt(uint8_t interrupt, uint32_t esp)
{
    if (activeInterruptManager != nullptr) {
        return activeInterruptManager->doHandleInterrupt(interrupt, esp);
    }
    return esp;
}

uint32_t InterruptManager::doHandleInterrupt(uint8_t interrupt, uint32_t esp) {
    if (handlers[interrupt] != 0) {
        esp = handlers[interrupt]->handleInterrupt(esp);
    } else if (interrupt != hardwareInterruptOffset) {
        char* foo = (char*) "UNHANDLED INTERRUPT 0x00";
        char* hex = (char*) "0123456789ABCDEF";
        foo[22] = hex[(interrupt >> 4) & 0xF];
        foo[23] = hex[interrupt & 0xF];
        kprint(foo);
    }

    // hardware interrupts must be acknowledged
    if (hardwareInterruptOffset <= interrupt && interrupt < hardwareInterruptOffset + 16) {
        programmableInterruptControllerMasterCommandPort.write(0x20);
        if (hardwareInterruptOffset + 8 <= interrupt) {
            programmableInterruptControllerSlaveCommandPort.write(0x20);
        }
    }

    return esp;
}