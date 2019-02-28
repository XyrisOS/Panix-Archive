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
const char commandNames[NUMBER_OF_COMMANDS][256] = {
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
    drivers::Screen::kprint((char*) "Panix:$ ");

    return 0;
}

/*******************
* Public Functions *
********************/
void panixkernel::Kernel::printPanicSplash() {
    drivers::Screen::clearScreen();
    const char* panicSplashScreen[8] = {
        " ___________________________ \n",
        "< Oops! Panix has panicked! >\n",
        " --------------------------- \n",
        "    \\   ^__^\n",
        "     \\  (**)\\_______\n",
        "        (__)\\       )\\/\\\n",
        "         U  ||----w |\n",
        "            ||     ||\n\n"
    };
    for (auto line : panicSplashScreen) {
        drivers::Screen::kprint((char*) line);
    }
}

void panixkernel::Kernel::printSplashScreen() {
    drivers::Screen::clearScreen();
    const char* splashScreen[7] = {
        "     ____  ___    _   _______  __ \n",
        "    / __ \\/   |  / | / /  _/ |/ /\n",
        "   / /_/ / /| | /  |/ // / |   /  \n",
        "  / ____/ ___ |/ /|  // / /   |   \n",
        " /_/   /_/  |_/_/ |_/___//_/|_|   \n",
        "\nWelcome to the PANIX kernel!\n",
        "\nType HALT to halt the CPU\n"
    };
    for (auto line : splashScreen) {
        drivers::Screen::kprint((char*) line);
    }
}

void panixkernel::Kernel::handleUserInput(char* input) {
    for (int i = 0; i < NUMBER_OF_COMMANDS; ++i) {
        if (stringComparison((char*) commandNames[i], input) == 0) {
            (*commandFunctions[i])();
            break;
        }
    }
    drivers::Screen::kprint((char*) "Panix:$ ");
}

void panixkernel::Kernel::help() {
    drivers::Screen::kprint((char*) "\nThe available commands are:\n");
    for (auto commandName : commandNames) {
        drivers::Screen::kprint((char*) commandName);
        drivers::Screen::kprint((char*) "\n");
    }
}

void panixkernel::Kernel::panic() {
    panixkernel::Kernel::printPanicSplash();
    int result = 0 / 0;
    result++;
}

void panixkernel::Kernel::printTick() {
    timer.printTick();
}