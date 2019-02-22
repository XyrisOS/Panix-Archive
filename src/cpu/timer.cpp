#include "timer.h"

uint32_t tick = 0;

static void timerCallback(registers_t regs) {
    tick++;
    if (false) {
        kprint((char*) "Tick: ");

        char tickString[256];
        intToString(tick, tickString);
        kprint(tickString);
        kprint((char*) "\n");
    }

    UNUSED(regs);
}

void initTimer(uint32_t frequency) {
    /* Install the function we just wrote */
    registerInterruptHandler(IRQ0, timerCallback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / frequency;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    portByteOut(0x43, 0x36); /* Command port */
    portByteOut(0x40, low);
    portByteOut(0x40, high);
}