/**
 * @file Timer.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief Programmable Interval Timer (not to be confused with the 
 * programmable interrupt controller like I initially was) is a chip
 * that runs at (roughly) 1.193182 Mhz and is used as a basic time
 * keeping mechanism through use of IRQ0. (Brief partially taken from
 * OSDev Wiki - wiki.osdev.org)
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
#include <cpu/interrupts/InterruptManager.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <cpu/port/Port.hpp>
#include <libc/string.hpp>
#include <libc/kprint.hpp>

class Timer : public InterruptHandler, public Driver {
    private:
        bool isTick;
        uint32_t tick;
        uint8_t high;
        uint8_t low;
        PortByte commandPort;
        PortByte dataPort;
    public:
        Timer(InterruptManager* interruptManager, int freq);
        ~Timer();
        void printTick();
        void activate();
        void deactivate();
        int reset();
        uint32_t handleInterrupt(uint32_t esp);
};

#endif /* PANIX_CPU_TIMER */