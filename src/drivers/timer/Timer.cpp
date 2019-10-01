/**
 * @file Timer.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <drivers/timer/Timer.hpp>

Timer::Timer(InterruptManager* interruptManager, int freq) :
InterruptHandler(interruptManager, 0x20) {
    isTick = true;
    tick = 0;
    uint32_t divisor = 1193182 / freq;
    low = (uint8_t)(divisor & 0xFF);
    high = ((uint8_t)(divisor >> 8) & 0xFF);
}

Timer::~Timer() {
    //kprint("Destroying CPU timer\n");
}

void Timer::activate() {
    kprint("Activating CPU programmable timer (PIT)\n");
    // Write to the command port
    writeByte(TIMER_COMMAND_PORT, 0x36);
    // Write to the data port
    writeByte(TIMER_DATA_PORT, low);
    writeByte(TIMER_DATA_PORT, high);
    tick = 0;
}

int Timer::reset() {
    tick = 0;
    return tick;
}

void Timer::deactivate() {
    // We can't deactivate the CPU timer
    tick = 0;
}

void Timer::printTick() {
    kprint("Tick: ");
    char tickStr[11];
    intToString(tick, tickStr);
    kprint(tickStr);
    kprint("\n");
}

uint32_t Timer::handleInterrupt(uint32_t esp) {
    tick++;
    return esp;
}

void Timer::sleep(uint32_t ticks) {
    uint32_t current = tick;
    uint32_t end = tick + ticks;
    while (current < end) {
        // Update current
        current = tick;
        // Do nothing and waste precious CPU cycles
        // like the monster we are.
    }
    return;
}

char* Timer::getDriverTypeTag() {
    return "PIT";
}