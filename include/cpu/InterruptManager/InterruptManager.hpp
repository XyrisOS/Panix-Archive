
#ifndef INTERRUPT_MANAGER_HPP
#define INTERRUPT_MANAGER_HPP

#include <cpu/GlobalDescriptorTable/GlobalDescriptorTable.hpp>
#include <types.hpp>
#include <cpu/Port/Port.hpp>

class InterruptManager
{
    //friend class InterruptHandler;
    protected:

        struct GateDescriptor
        {
            uint16_t handlerAddressLowBits;
            uint16_t gdt_codeSegmentSelector;
            uint8_t reserved;
            uint8_t access;
            uint16_t handlerAddressHighBits;
        } __attribute__((packed));

        static GateDescriptor interruptDescriptorTable[256];

        struct InterruptDescriptorTablePointer
        {
            uint16_t size;
            uint32_t base;
        } __attribute__((packed));

        uint16_t interruptOffset;
        static InterruptManager* activeInterruptManager;
        static void setInterruptDescriptorTableEntry(uint8_t interrupt,
            uint16_t codeSegmentSelectorOffset, void (*handler)(),
            uint8_t DescriptorPrivilegeLevel, uint8_t DescriptorType);


        static void interruptIgnore();

        static void handleInterruptRequest0x00();
        static void handleInterruptRequest0x01();
        static void handleInterruptRequest0x02();
        static void handleInterruptRequest0x03();
        static void handleInterruptRequest0x04();
        static void handleInterruptRequest0x05();
        static void handleInterruptRequest0x06();
        static void handleInterruptRequest0x07();
        static void handleInterruptRequest0x08();
        static void handleInterruptRequest0x09();
        static void handleInterruptRequest0x0A();
        static void handleInterruptRequest0x0B();
        static void handleInterruptRequest0x0C();
        static void handleInterruptRequest0x0D();
        static void handleInterruptRequest0x0E();
        static void handleInterruptRequest0x0F();
        static void handleInterruptRequest0x31();

        static void handleException0x00();
        static void handleException0x01();
        static void handleException0x02();
        static void handleException0x03();
        static void handleException0x04();
        static void handleException0x05();
        static void handleException0x06();
        static void handleException0x07();
        static void handleException0x08();
        static void handleException0x09();
        static void handleException0x0A();
        static void handleException0x0B();
        static void handleException0x0C();
        static void handleException0x0D();
        static void handleException0x0E();
        static void handleException0x0F();
        static void handleException0x10();
        static void handleException0x11();
        static void handleException0x12();
        static void handleException0x13();

        static uint32_t handleInterrupt(uint8_t interrupt, uint32_t esp);

        Port8BitSlow programmableInterruptControllerMasterCommandPort;
        Port8BitSlow programmableInterruptControllerMasterDataPort;
        Port8BitSlow programmableInterruptControllerSlaveCommandPort;
        Port8BitSlow programmableInterruptControllerSlaveDataPort;

    public:
        InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* globalDescriptorTable);
        ~InterruptManager();
        uint16_t hardwareInterruptOffset();
        void activate();
        void deactivate();
};

#endif /* INTERRUPT_MANAGER_HPP */