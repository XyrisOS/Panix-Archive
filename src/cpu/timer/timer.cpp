/**
 * @file timer.cpp
 * @author Keeton Feavel and James Osborne
 * @brief Timer definitions file
 * @version 0.1
 * @date 2019-02-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "timer.h"

using namespace cpu;
using namespace drivers;

uint32_t tick = 0;

/*******************
* Public Functions *
********************/
void Timer::initialize(uint32_t frequency) {
    /* Install the function we just wrote */
    ISR::registerInterruptHandler(IRQ0, Timer::callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / frequency;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    Ports::setPortByte(0x43, 0x36); /* Command port */
    Ports::setPortByte(0x40, low);
    Ports::setPortByte(0x40, high);
}

void Timer::printTick() {
    drivers::Screen::kprint("Tick: ");
    char tickString[10];
    intToString(tick, tickString);
    drivers::Screen::kprint(tickString);
    drivers::Screen::kprintNewLine();
}

/********************
* Private Functions *
*********************/
void Timer::callback(registers_t regs) {
    tick++;

    UNUSED(regs);
}