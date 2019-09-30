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
// Remember that our hardware offset is 0x20, and the PIT has an IRQ of 0x00
// so we have to register for 0x20 + 0x00 = 0x20.
    InterruptHandler(interruptManager, 0x20),
    commandPort(0x43), 
    dataPort(0x40)
{
    isTick = true;
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
    commandPort.write(0x36);
    // Write to the data port
    dataPort.write(low);
    dataPort.write(high);
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

uint32_t Timer::handleInterrupt(uint32_t esp) {
    tick++;
    return esp;
}

void Timer::sleep(uint32_t ticks) {

}

char* Timer::getDriverTypeTag() {
    return "PIT";
}