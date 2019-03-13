/**
 * @file kernel.cpp
 * @author Keeton Feavel and James Osborne
 * @brief Panix kernel main source file.
 * Includes the kernel's kernel_main() function
 * that helps make the jump from 16-bit
 * real mode out of assembly and into the
 * 32-bit protected mode where out kernel
 * will be executing.
 * @version 0.1
 * @date 2019-02-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "kernel.h"

inline cpu::Timer timer;
inline panixkernel::Kernel kernel;

#define NUMBER_OF_COMMANDS 5
const char commandNames[NUMBER_OF_COMMANDS][16] = {
    "CLEAR",
    "HELP",
    "PANIC",
    "SPLASH",
    "TICK"
};
void (*commandFunctions[NUMBER_OF_COMMANDS])();

/**
 * @brief Main entry point for the kernel
 * 
 */
extern "C" int kernelMain() {
    cpu::ISR::isrInstall();
    cpu::ISR::irqInstall();

    /* Initialize function pointers */
    commandFunctions[0] = drivers::Screen::clearScreen;
    commandFunctions[1] = panixkernel::Kernel::help;
    commandFunctions[2] = panixkernel::Kernel::panic;
    commandFunctions[3] = panixkernel::Kernel::printSplashScreen;
    commandFunctions[4] = panixkernel::Kernel::printTick;

    kernel.printSplashScreen();
    drivers::Screen::kprint("Panix:$ ");

    return 0;
}

/*******************
* Public Functions *
********************/
void panixkernel::Kernel::printSplashScreen() {
    drivers::Screen::clearScreen();

    drivers::Screen::kprint("Welcome to the PANIX kernel!"); drivers::Screen::kprintNewLine(); drivers::Screen::kprintNewLine();
}

void panixkernel::Kernel::handleUserInput(char* input) {
    for (int i = 0; i < NUMBER_OF_COMMANDS; ++i) {
        if (stringComparison((char*) commandNames[i], input) == 0) {
            (*commandFunctions[i])();
            break;
        }
    }
    drivers::Screen::kprint("Panix:$ ");
}

void panixkernel::Kernel::help() {
    drivers::Screen::kprint("The available commands are:");
    drivers::Screen::kprintNewLine();
    for (auto commandName : commandNames) {
        drivers::Screen::kprint(commandName);
        drivers::Screen::kprintNewLine();
    }
}

void panixkernel::Kernel::panic() {
    drivers::Screen::kprint("< Oops! Panix has panicked! >"); drivers::Screen::kprintNewLine();
    int result = 0 / 0;
    result++;
}

void panixkernel::Kernel::printTick() {
    timer.printTick();
}