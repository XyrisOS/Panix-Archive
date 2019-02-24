/**
 * File: idt.cpp
 * Author: Keeton Feavel and James Osborne
 */

#include "idt.h"

/*******************
* Public Functions *
********************/

void IDT::setIdtGate(int n, uint32_t handler) {
    idt[n].lowOffset = low16(handler);
    idt[n].selector = KERNEL_CS;
    idt[n].alwaysZero = 0;
    idt[n].flags = 0x8E; 
    idt[n].highOffset = high16(handler);
}

void IDT::setIdt() {
    idtRegister.base = (uint32_t) &idt;
    idtRegister.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    asm volatile("lidtl (%0)" : : "r" (&idtRegister));
}