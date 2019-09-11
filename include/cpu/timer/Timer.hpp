#ifndef PANIX_CPU_TIMER
#define PANIX_CPU_TIMER

#include <types.hpp>
#include <cpu/port/Port.hpp>
#include <libc/string.hpp>
#include <libc/kprint.hpp>

class Timer {
    private:
        bool isTick;
        uint32_t tick;
        Port8Bit commandPort;
        Port8Bit dataPort;
    public:
        Timer(int freq);
        ~Timer();
        void callback();
};

#endif /* PANIX_CPU_TIMER */