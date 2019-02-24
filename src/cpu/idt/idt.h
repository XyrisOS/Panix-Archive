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
/* `inline` prevents a multiple definition error */
inline idt_gate_t idt[IDT_ENTRIES];
inline idt_register_t idtRegister;

/* Functions implemented in idt.c */
void setIdtGate(int n, uint32_t handler);
void setIdt();

#endif /* IDT_H */