/**
 * @file kernel.h
 * @author Keeton Feavel and James Osborne
 * @brief Kernel header file
 * @version 0.1
 * @date 2019-02-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef KERNEL_H
#define KERNEL_H

#include "../cpu/idt/idt.h"
#include "../cpu/isr/isr.h"
#include "../cpu/ports/ports.h"
#include "../cpu/timer/timer.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/mouse/mouse.h"
#include "../drivers/screen/screen.h"

namespace panixkernel {
    class Kernel {
        public:
            /**
             * @brief Handles all keyboard input for the basic kernel shell.
             * 
             * @param input String input from keyboard to be processed.
             */
            void handleUserInput(char* input);

            /**
             * @brief Prints list of available commands
             * 
             */
            static void help();

            /**
             * @brief Divides by zero to halt the CPU
             * 
             */
            static void panic();

            /**
             * @brief Prints the panic splash 
             * 
             */
            static void printPanicSplash();

            /**
             * @brief Prints the Panix splash screen on boot.
             * 
             */
            static void printSplashScreen();

            /**
             * @brief Prints the current tick of the CPU
             * 
             */
            static void printTick();
    };
}

#endif /* KERNEL_H */