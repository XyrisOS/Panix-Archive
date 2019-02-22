#include "timer.h"
#include "../drivers/screen.h"
#include "../kernel/util/util.h"
#include "isr.h"

uint32_t tick = 0;

static void timerCallback(registers_t regs) {
    tick++;
    kprint((char*) "Tick: ");
    
    char tickString[256];
    int_to_ascii(tick, tickString);
    kprint(tickString);
    kprint((char*) "\n");
}

void initTimer(uint32_t freq) {
    /* Install the function we just wrote */
    registerInterruptHandler(IRQ0, timerCallback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / freq;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}