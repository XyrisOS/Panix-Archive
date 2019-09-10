#ifndef PANIX_CPU_TIMER
#define PANIX_CPU_TIMER

#include <types.hpp>
#include <libc/string.hpp>
#include <libc/kprint.hpp>

class Timer {
    private:
        bool isTick;
        uint32_t tick;
    public:
        Timer();
        ~Timer();
        void activate();
        void deactivate();
        void callback();
};

#endif /* PANIX_CPU_TIMER */