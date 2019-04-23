
#ifndef INTERRUPT_MANAGER_HPP
#define INTERRUPT_MANAGER_HPP

#include <cpu/GlobalDescriptorTable/GlobalDescriptorTable.hpp>
#include <types.hpp>
#include <cpu/Port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>

/* Forward declaration */
class InterruptHandler;

class InterruptManager {
    friend class InterruptHandler;
    protected:
        uint16_t hardwareInterruptOffset;
        static InterruptManager* activeInterruptManager;
        InterruptHandler* handlers[256];
        /**
         * @brief 
         * 
         */
        struct GateDescriptor {
            uint16_t handlerAddressLowBits;
            uint16_t gdt_codeSegmentSelector;
            uint8_t reserved;
            uint8_t access;
            uint16_t handlerAddressHighBits;
        } __attribute__((packed));
        /**
         * @brief 
         * 
         */
        static GateDescriptor interruptDescriptorTable[256];
        /**
         * @brief 
         * 
         */
        struct InterruptDescriptorTablePointer {
            uint16_t size;
            uint32_t base;
        } __attribute__((packed));
        /**
         * @brief Set the Interrupt Descriptor Table Entry object
         * 
         * @param interrupt 
         * @param codeSegmentSelectorOffset 
         * @param handler 
         * @param DescriptorPrivilegeLevel 
         * @param DescriptorType 
         */
        static void setInterruptDescriptorTableEntry(uint8_t interrupt,
            uint16_t codeSegmentSelectorOffset, void (*handler)(),
            uint8_t DescriptorPrivilegeLevel, uint8_t DescriptorType);

        /**
         * @brief 
         * 
         */
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
        /**
         * @brief 
         * 
         * @param interrupt 
         * @param esp 
         * @return uint32_t 
         */
        static uint32_t handleInterrupt(uint8_t interrupt, uint32_t esp);
        uint32_t doHandleInterrupt(uint8_t interrupt, uint32_t esp);

        Port8BitSlow programmableInterruptControllerMasterCommandPort;
        Port8BitSlow programmableInterruptControllerMasterDataPort;
        Port8BitSlow programmableInterruptControllerSlaveCommandPort;
        Port8BitSlow programmableInterruptControllerSlaveDataPort;

    public:
        /**
         * @brief Construct a new Interrupt Manager object
         * 
         * @param hardwareInterruptOffset 
         * @param globalDescriptorTable 
         */
        InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* globalDescriptorTable);
        /**
         * @brief Destroy the Interrupt Manager object
         * 
         */
        ~InterruptManager();
        /**
         * @brief Get the Hardware Interrupt Offset object
         * 
         * @return uint16_t 
         */
        uint16_t getHardwareInterruptOffset();
        /**
         * @brief 
         * 
         */
        void activate();
        /**
         * @brief 
         * 
         */
        void deactivate();
};

#endif /* INTERRUPT_MANAGER_HPP */