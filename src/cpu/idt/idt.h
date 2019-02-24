/**
 * @file idt.h
 * @author Keeton Feavel and James Osborne
 * @brief Interrupt Descriptor Table
 * @version 0.1
 * @date 2019-02-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef IDT_H
#define IDT_H

#include "../type.h"

/* Segment selectors */
#define KERNEL_CS 0x08

#define IDT_ENTRIES 256

class IDT {
    public:
        /**
         * @brief Set the IDT fields and initalize with KERNEL_CS
         * 
         * @param n The index of the gate to set
         * @param handler The register to link to the IDT gate
         */
        static void setIdtGate(int n, uint32_t handler);

        /**
         * @brief Set the IDT base and limit
         * 
         */
        static void setIdt();

    private:
        /**
         * @brief Holds all of the entries of the IDT
         * 
         */
        static inline idt_gate_t idt[IDT_ENTRIES];
        /**
         * @brief The reference to the IDT register
         * 
         */
        static inline idt_register_t idtRegister;
};

#endif /* IDT_H */