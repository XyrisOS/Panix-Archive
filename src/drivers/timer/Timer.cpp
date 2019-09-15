#include <drivers/timer/Timer.hpp>

Timer::Timer(int freq) : 
    commandPort(0x43), 
    dataPort(0x40)
{
    isTick = true;
    uint32_t divisor = 1193180 / freq;
    low = (uint8_t)(divisor & 0xFF);
    high = ((uint8_t)(divisor >> 8) & 0xFF);
}

Timer::~Timer() {
    kprint("Destroying CPU timer\n");
}

void Timer::activate() {
    kprint("Activating CPU programmable timer\n");
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

void Timer::callback() {
    tick++;
}