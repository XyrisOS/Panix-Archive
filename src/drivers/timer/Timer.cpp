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

Timer::Timer(int freq) {
    isTick = true;
    uint32_t divisor = 1193180 / freq;
    low = (uint8_t)(divisor & 0xFF);
    high = ((uint8_t)(divisor >> 8) & 0xFF);
}

Timer::~Timer() {
    //kprint("Destroying CPU timer\n");
}

void Timer::activate() {
    kprint("Activating CPU programmable timer\n");
    // Write to the command port
    writeByte(TIMER_COMMAND_PORT, 0x36);
    // Write to the data port
    writeByte(TIMER_DATA_PORT, low);
    writeByte(TIMER_DATA_PORT, high);
}

int Timer::reset() {
    tick = 0;
    return tick;
}

void Timer::deactivate() {
    // We can't deactivate the CPU timer
}

void Timer::printTick() {
    kprint("Tick: ");
    char tickStr[10];
    intToString(tick, tickStr);
    kprint(tickStr);
    kprint("\n");
}

void Timer::callback() {
    tick++;
}