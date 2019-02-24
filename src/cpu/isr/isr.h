/**
 * File: isr.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef ISR_H
#define ISR_H

#include "../../drivers/screen/screen.h"
#include "../../kernel/kernel.h"
#include "../../libc/string.h"
#include "../idt/idt.h"
#include "../ports/ports.h"
#include "../timer/timer.h"
#include "../type.h"

/**
 * @brief 
 * 
 */
extern "C" {
    /* ISRs reserved for CPU exceptions */
    void isr0();
    void isr1();
    void isr2();
    void isr3();
    void isr4();
    void isr5();
    void isr6();
    void isr7();
    void isr8();
    void isr9();
    void isr10();
    void isr11();
    void isr12();
    void isr13();
    void isr14();
    void isr15();
    void isr16();
    void isr17();
    void isr18();
    void isr19();
    void isr20();
    void isr21();
    void isr22();
    void isr23();
    void isr24();
    void isr25();
    void isr26();
    void isr27();
    void isr28();
    void isr29();
    void isr30();
    void isr31();

    /* IRQ definitions */
    void irq0();
    void irq1();
    void irq2();
    void irq3();
    void irq4();
    void irq5();
    void irq6();
    void irq7();
    void irq8();
    void irq9();
    void irq10();
    void irq11();
    void irq12();
    void irq13();
    void irq14();
    void irq15();
}

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

/**
 * @brief 
 * 
 */
void irqInstall();

/**
 * @brief 
 * 
 */
void isrInstall();

/**
 * @brief 
 * 
 */
extern "C" {
    void irqHandler(registers_t r);
    void isrHandler(registers_t r);
}

/**
 * @brief 
 * 
 */
typedef void (*isr_t)(registers_t);

/**
 * @brief 
 * 
 * @param n 
 * @param handler 
 */
void registerInterruptHandler(uint8_t n, isr_t handler);

#endif