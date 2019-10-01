/**
 * @file InterruptManager.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_INTERRUPT_MANAGER_HPP
#define PANIX_INTERRUPT_MANAGER_HPP

#include <types.hpp>
#include <cpu/port/Port.hpp>
#include <cpu/gdt/GlobalDescriptorTable.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <cpu/multitasking/Multitasking.hpp>
#include <drivers/speaker/Speaker.hpp>
#include <libc/stdio.hpp>
#include <libc/string.hpp>
#include <libc/kprint.hpp>
#include <libc/tty.hpp>

#define MASTER_COMMAND 0x20
#define MASTER_DATA 0x21
#define SLAVE_COMMAND 0xA0
#define SLAVE_DATA 0xA1

/* Forward declaration */
class InterruptHandler;

class InterruptManager {
    friend class InterruptHandler;
    protected:
        // Data structures
        struct GateDescriptor {
            uint16_t handlerAddressLowBits;
            uint16_t gdt_codeSegmentSelector;
            uint8_t reserved;
            uint8_t access;
            uint16_t handlerAddressHighBits;
        } __attribute__((packed));
        
        struct InterruptDescriptorTablePointer {
            uint16_t size;
            uint32_t base;
        } __attribute__((packed));
        // Define the PIC CPU ports
        PortByteSlow programmableInterruptControllerMasterCommandPort;
        PortByteSlow programmableInterruptControllerMasterDataPort;
        PortByteSlow programmableInterruptControllerSlaveCommandPort;
        PortByteSlow programmableInterruptControllerSlaveDataPort;
        // Interrupt vs. exception offset
        uint16_t hardwareInterruptOffset;
        // Active managers
        static InterruptManager* activeInterruptManager;
        TaskManager* activeTaskManager;
        // Array of handler functions
        InterruptHandler* handlers[256];
        static GateDescriptor interruptDescriptorTable[256];
        const uint8_t IDT_INTERRUPT_GATE = 0xE;
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
         * @brief Ignores a given interrupt. Used as a handler function.
         * 
         */
        static void interruptIgnore();
        /**
         * @brief Interrupt handler functions
         * 
         */
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
        /**
         * @brief Exception handler functions
         * 
         */
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
         * @brief Handles an interrupt from the CPU.
         * 
         * @param interrupt Interrupt code
         * @param esp Stack pointer
         * @return uint32_t Returned stack pointer
         */
        static uint32_t handleInterrupt(uint8_t interrupt, uint32_t esp);
        
    public:
        /**
         * @brief Construct a new Interrupt Manager object
         * 
         * @param hardwareInterruptOffset 
         * @param globalDescriptorTable 
         */
        InterruptManager(uint16_t hardwareInterruptOffset, GlobalDescriptorTable* globalDescriptorTable, TaskManager* taskManager);
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
         * @brief Activates the interrupt and exception handlers
         * 
         */
        void activate();
        /**
         * @brief Deactivates the interrupt and exception handlers
         * 
         */
        void deactivate();
};

#endif /* PANIX_INTERRUPT_MANAGER_HPP */