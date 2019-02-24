/**
 * File: idt.h
 * Author: Keeton Feavel and James Osborne
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

#endif