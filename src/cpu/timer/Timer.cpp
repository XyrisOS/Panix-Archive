#include <cpu/timer/Timer.hpp>

Timer::Timer() {
    isTick = true;
    kprint("Initializing CPU timer...\n");
}

Timer::~Timer() {
    kprint("Destroying CPU timer...\n");
}

void Timer::activate() {
    kprint("Activating CPU timer...\n");
}

void Timer::deactivate() {
    kprint("Deactivating CPU timer...\n");
}

void Timer::callback() {
    if (isTick) {
        //kprint("Tick. ");
        isTick = false;
    } else {
        //kprint("Tock. ");
        isTick = true;
    }
}