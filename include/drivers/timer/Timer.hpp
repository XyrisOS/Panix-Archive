/**
 * @file Timer.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_CPU_TIMER
#define PANIX_CPU_TIMER

#include <types.hpp>
#include <drivers/Driver.hpp>
#include <cpu/port/Port.hpp>
#include <libc/string.hpp>
#include <libc/kprint.hpp>

class Timer : public Driver {
    private:
        bool isTick;
        uint32_t tick;
        uint8_t high;
        uint8_t low;
        PortByte commandPort;
        PortByte dataPort;
    public:
        Timer(int freq);
        ~Timer();
        void printTick();
        void callback();
        void activate();
        int reset();
        void deactivate();
};

#endif /* PANIX_CPU_TIMER */