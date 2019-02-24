/**
 * @file timer.h
 * @author Keeton Feavel and James Osborne
 * @brief CPU Timer header file. Provides
 * a class to access the timer on the CPU.
 * @version 0.1
 * @date 2019-02-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TIMER_H
#define TIMER_H

#include "../../drivers/screen/screen.h"
#include "../../libc/string/string.h"
#include "../isr/isr.h"
#include "../ports/ports.h"
#include "../type.h"

namespace cpu {
    class Timer {
        public:
            /**
             * @brief Initializes the CPU timer
             * 
             * @param frequency I honestly do not know
             */
            void initialize(uint32_t frequency);

            /**
             * @brief Prints the current ticks
             * 
             */
            void printTick();
        
        private:
            /**
             * @brief Prints to the screen the current ticks of the CPU.
             * 
             * @param regs Currently unused registers
             */
            static void callback(registers_t regs);
    };
}

#endif /* TIMER_H */