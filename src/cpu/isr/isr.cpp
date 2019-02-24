/**
 * @file isr.cpp
 * @author Keeton Feavel and James Osborne
 * @brief Interrupt Service Routine definitions file
 * @version 0.1
 * @date 2019-02-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "isr.h"

using namespace cpu;
using namespace drivers;

const char panicSplashScreen[8][32] = {
    " ___________________________ \n",
    "< Oops! Panix has panicked! >\n",
    " --------------------------- \n",
    "    \\   ^__^\n",
    "     \\  (**)\\_______\n",
    "        (__)\\       )\\/\\\n",
    "         U  ||----w |\n",
    "            ||     ||\n\n"
};

/* To print the message which defines every exception */
const char exceptionMessages[32][32] {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

isr_t interruptHandlers[256];

/*******************
* Public Functions *
********************/

void ISR::irqInstall() {
    /* Enable interruptions */
    asm volatile("sti");

    /* IRQ0: timer */
    Timer::initialize(50);
    /* IRQ1: keyboard */
    Keyboard keyboard;
    keyboard.initialize();
}

/* Can't do this with a loop because we need the address
 * of the function names */
void ISR::isrInstall() {
    IDT::setIdtGate(0, (uint32_t) isr0);
    IDT::setIdtGate(1, (uint32_t) isr1);
    IDT::setIdtGate(2, (uint32_t) isr2);
    IDT::setIdtGate(3, (uint32_t) isr3);
    IDT::setIdtGate(4, (uint32_t) isr4);
    IDT::setIdtGate(5, (uint32_t) isr5);
    IDT::setIdtGate(6, (uint32_t) isr6);
    IDT::setIdtGate(7, (uint32_t) isr7);
    IDT::setIdtGate(8, (uint32_t) isr8);
    IDT::setIdtGate(9, (uint32_t) isr9);
    IDT::setIdtGate(10, (uint32_t) isr10);
    IDT::setIdtGate(11, (uint32_t) isr11);
    IDT::setIdtGate(12, (uint32_t) isr12);
    IDT::setIdtGate(13, (uint32_t) isr13);
    IDT::setIdtGate(14, (uint32_t) isr14);
    IDT::setIdtGate(15, (uint32_t) isr15);
    IDT::setIdtGate(16, (uint32_t) isr16);
    IDT::setIdtGate(17, (uint32_t) isr17);
    IDT::setIdtGate(18, (uint32_t) isr18);
    IDT::setIdtGate(19, (uint32_t) isr19);
    IDT::setIdtGate(20, (uint32_t) isr20);
    IDT::setIdtGate(21, (uint32_t) isr21);
    IDT::setIdtGate(22, (uint32_t) isr22);
    IDT::setIdtGate(23, (uint32_t) isr23);
    IDT::setIdtGate(24, (uint32_t) isr24);
    IDT::setIdtGate(25, (uint32_t) isr25);
    IDT::setIdtGate(26, (uint32_t) isr26);
    IDT::setIdtGate(27, (uint32_t) isr27);
    IDT::setIdtGate(28, (uint32_t) isr28);
    IDT::setIdtGate(29, (uint32_t) isr29);
    IDT::setIdtGate(30, (uint32_t) isr30);
    IDT::setIdtGate(31, (uint32_t) isr31);

    /* Remap the PIC */
    Ports::setPortByte(0x20, 0x11);
    Ports::setPortByte(0xA0, 0x11);
    Ports::setPortByte(0x21, 0x20);
    Ports::setPortByte(0xA1, 0x28);
    Ports::setPortByte(0x21, 0x04);
    Ports::setPortByte(0xA1, 0x02);
    Ports::setPortByte(0x21, 0x01);
    Ports::setPortByte(0xA1, 0x01);
    Ports::setPortByte(0x21, 0x0);
    Ports::setPortByte(0xA1, 0x0); 

    /* Install the IRQs */
    IDT::setIdtGate(32, (uint32_t)irq0);
    IDT::setIdtGate(33, (uint32_t)irq1);
    IDT::setIdtGate(34, (uint32_t)irq2);
    IDT::setIdtGate(35, (uint32_t)irq3);
    IDT::setIdtGate(36, (uint32_t)irq4);
    IDT::setIdtGate(37, (uint32_t)irq5);
    IDT::setIdtGate(38, (uint32_t)irq6);
    IDT::setIdtGate(39, (uint32_t)irq7);
    IDT::setIdtGate(40, (uint32_t)irq8);
    IDT::setIdtGate(41, (uint32_t)irq9);
    IDT::setIdtGate(42, (uint32_t)irq10);
    IDT::setIdtGate(43, (uint32_t)irq11);
    IDT::setIdtGate(44, (uint32_t)irq12);
    IDT::setIdtGate(45, (uint32_t)irq13);
    IDT::setIdtGate(46, (uint32_t)irq14);
    IDT::setIdtGate(47, (uint32_t)irq15);

    IDT::setIdt(); /* Load with ASM */
}

void ISR::printKernelPanicSplash() {
    Screen::clearScreen();
    for (int i = 0; i < 8; i++) {
        Screen::kprint((char*) panicSplashScreen[i]);
    }
}

void ISR::registerInterruptHandler(uint8_t n, isr_t handler) {
    interruptHandlers[n] = handler;
}

void irqHandler(registers_t r) {
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    
    /* slave */
    if (r.interruptNumber >= 40) {
        Ports::setPortByte(0xA0, 0x20);
    }
    /* master */
    Ports::setPortByte(0x20, 0x20); 

    /* Handle the interrupt in a more modular way */
    if (interruptHandlers[r.interruptNumber] != 0) {
        isr_t handler = interruptHandlers[r.interruptNumber];
        handler(r);
    }
}

void isrHandler(registers_t r) {
    /* TODO: Write a panic message. Maybe animate it? */
    Screen::clearScreen();
    ISR::printKernelPanicSplash();
    Screen::kprint((char*) "\n");
    Screen::kprint((char*) exceptionMessages[r.interruptNumber]);
    Screen::kprint((char*) "\n");
    asm volatile("hlt");
}