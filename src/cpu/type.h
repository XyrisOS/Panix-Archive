/**
 * @file type.h
 * @author Keeton Feavel and James Osborne
 * @brief Defines various special types and includes stdint.h
 * @version 0.1
 * @date 2019-02-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TYPE_H
#define TYPE_H

#include <stdint.h>

#define low16(address) (uint16_t)((address) & 0xFFFF)
#define high16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

/* Struct which aggregates many registers */
/**
 * @brief 
 * 
 */
typedef struct {
    /* Data segment selector */
    uint32_t ds;

    /* Pushed by pusha. */
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax; 

    /* Interrupt number and error code (if applicable) */
    uint32_t interruptNumber;
    uint32_t errorCode;

    /* Pushed by the processor automatically */
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t useresp;
    uint32_t ss;
} registers_t;

/* How every interrupt gate (handler) is defined */
typedef struct {
    uint16_t lowOffset; /* Lower 16 bits of handler function address */
    uint16_t selector; /* Kernel segment selector */
    uint8_t alwaysZero;
    /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
    uint8_t flags; 
    uint16_t highOffset; /* Higher 16 bits of handler function address */
} __attribute__((packed)) idt_gate_t;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

/**
 * @brief Defines a new type which defines an array of isr_t as registers_t
 * 
 */
typedef void (*isr_t)(registers_t);

#endif /* TYPE_H */