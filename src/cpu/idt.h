#ifndef IDT_H
#define IDT_H

#include "types.h"

/* Segment selectors */
#define KERNEL_CS 0x08

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
} __attribute__((packed)) idt_gate_t ;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
/* `inline` prevents a multiple definition error */
inline idt_gate_t idt[IDT_ENTRIES];
inline idt_register_t idtRegister;

/* Functions implemented in idt.c */
void setIdtGate(int n, uint32_t handler);
void setIdt();

#endif