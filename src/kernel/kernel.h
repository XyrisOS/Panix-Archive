/**
 * File: kernel.cpp
 * Author: Keeton Feavel and James Osborne
 */

#ifndef KERNEL_H
#define KERNEL_H

#include "../cpu/idt/idt.h"
#include "../cpu/isr/isr.h"
#include "../cpu/ports/ports.h"
#include "../cpu/timer/timer.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/screen/screen.h"

class Kernel {
    public:
        /**
         * @brief Handles all keyboard input for the basic kernel shell.
         * 
         * @param input String input from keyboard to be processed.
         */
        static void handleUserInput(char* input);

        /**
         * @brief Prints the Panix splash screen on boot.
         * 
         */
        static void printSplashScreen();
};

#endif /* KERNEL_H */