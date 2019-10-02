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
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_CPU_TIMER
#define PANIX_CPU_TIMER

#include <common/types.hpp>
#include <drivers/Driver.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <cpu/port/Port.hpp>
#include <lib/string.hpp>
#include <lib/kprint.hpp>

#define TIMER_COMMAND_PORT 0x43
#define TIMER_DATA_PORT 0x40

class Timer : public Driver, public InterruptHandler {
    private:
        bool isTick;
        uint32_t tick;
        uint8_t high;
        uint8_t low;
        
    public:
        Timer(InterruptManager* interruptManager, int freq);
        ~Timer();
        void printTick();
        void activate();
        void deactivate();
        int reset();
        /**
         * @brief 
         * 
         * @param esp 
         * @return uint32_t 
         */
        uint32_t handleInterrupt(uint32_t esp);
        /**
         * @brief Returns the short tag type of the driver. Used to identify
         * the driver and its purpose. Used by the driver manager to get a
         * specific driver type.
         * 
         * @return char* Short driver type tag
         */
        char* getDriverTypeTag();
        /**
         * @brief Waits until a given number of ticks have passed before returning.
         * Please note, this is a really awful sleep function that eats up CPU cycles
         * without purpose. This should basically never be used other than just testing
         * since it practically halts all of the kernel until it returns.
         * 
         * @param ticks Number of PIT ticks to sleep for.
         */
        void sleep(uint32_t ticks);
};

#endif /* PANIX_CPU_TIMER */