/**
 * @file InterruptManager.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief The Interrupt Descriptor Table (IDT) is specific to the IA-32 architecture. 
 * It is the Protected mode counterpart to the Real Mode Interrupt Vector Table (IVT) 
 * telling where the Interrupt Service Routines (ISR) are located 
 * (one per interrupt vector) - https://wiki.osdev.org/Interrupt_Descriptor_Table
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_INTERRUPT_MANAGER_HPP
#define PANIX_INTERRUPT_MANAGER_HPP

#include <common/types.hpp>
#include <cpu/port/Port.hpp>
#include <cpu/gdt/GlobalDescriptorTable.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <cpu/multitasking/Multitasking.hpp>
#include <drivers/speaker/Speaker.hpp>
#include <lib/stdio.hpp>
#include <lib/string.hpp>
#include <lib/kprint.hpp>
#include <lib/tty.hpp>

// PIC Port Definitions
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
            uint16_t handlerAddressLowBits;     // Offset
            uint16_t gdt_codeSegmentSelector;   // a code segment selector in GDT or LDT
            uint8_t reserved;                   // unused, set to 0
            uint8_t access;                     // type and attributes, see below
            uint16_t handlerAddressHighBits;    // offset bits 16..31
        } __attribute__((packed));
        
        struct InterruptDescriptorTablePointer {
            uint16_t size;                      // Defines the length of the IDT in bytes - 1 (minimum value is 100h, a value of 1000h means 200h interrupts).
            uint32_t base;                      // This 32 bits are the linear address where the IDT starts (INT 0)
        } __attribute__((packed));
        // Array of handler functions
        InterruptHandler* handlers[256];                        // Array for all of the IRQ handlers (256 total for x86)
        static GateDescriptor interruptDescriptorTable[256];    // Array of all the created GateDescriptors
        // Interrupt vs. exception offset
        uint16_t hardwareInterruptOffset;       // Offset to differentiate between IRQs and Exceptions
        const uint8_t IDT_INTERRUPT_GATE = 0xE; // 32-bit interrupt gate defintion (see OSDev Wiki)
        /**
         * @brief Set the Interrupt Descriptor Table Entry object
         * 
         * @param interrupt Appropriate interrupt value (not including the hardware offset)
         * @param codeSegmentSelectorOffset Code segment selector for GDT or LDT
         * @param handler Handler function pointer
         * @param DescriptorPrivilegeLevel Specifies which privilege Level the calling Descriptor minimum should have.
         * @param DescriptorType The type of interrupt descriptor (???)
         */
        static void setInterruptDescriptorTableEntry(uint8_t interrupt,
            uint16_t codeSegmentSelectorOffset, void (*handler)(),
            uint8_t DescriptorPrivilegeLevel, uint8_t DescriptorType);      // Go to the OSDev Wiki for PrivilegeLevel explaination.
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
        // Active managers
        static InterruptManager* activeInterruptManager;
        /**
         * @brief Construct a new Interrupt Manager object
         * 
         * @param hardwareInterruptOffset Sets the hardware offset to differentiate IRQs and Exceptions
         * @param globalDescriptorTable Predefined GDT object to be used
         * @param taskManager Active task manager object to help switch process stacks
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
         * @return uint16_t Returns the set hardware interrupt offset
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