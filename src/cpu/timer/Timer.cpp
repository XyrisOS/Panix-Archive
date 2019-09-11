#include <cpu/timer/Timer.hpp>

Timer::Timer(int freq) : 
    commandPort(0x43), 
    dataPort(0x40)
{
    kprint("Initializing CPU timer...\n");
    isTick = true;
    uint32_t divisor = 1193180 / freq;
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = ((uint8_t)(divisor >> 8) & 0xFF);
    // Write to the command port
    commandPort.write(0x36);
    // Write to the data port
    dataPort.write(low);
    dataPort.write(high);
}

Timer::~Timer() {
    // kprint("Destroying CPU timer...\n");
}

void Timer::callback() {
    tick++;
}