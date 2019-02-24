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

/**
 * @brief Main entry point for the kernel
 * 
 */
extern "C" int kernelMain() {
    cpu::ISR::isrInstall();
    cpu::ISR::irqInstall();

    Kernel::printSplashScreen();
    Screen::kprint((char*) "Panix:$ ");

    return 0;
}

/*******************
* Public Functions *
********************/

void Kernel::printSplashScreen() {
    Screen::clearScreen();
    char* splashScreen[] = {
        (char*) "     ____  ___    _   _______  __ \n",
        (char*) "    / __ \\/   |  / | / /  _/ |/ /\n",
        (char*) "   / /_/ / /| | /  |/ // / |   /  \n",
        (char*) "  / ____/ ___ |/ /|  // / /   |   \n",
        (char*) " /_/   /_/  |_/_/ |_/___//_/|_|   \n",
        (char*) "\nWelcome to the PANIX kernel!\n",
        (char*) "\nType HALT to halt the CPU\n"
    };
    for (int i = 0; i < 7; i++) {
        Screen::kprint(splashScreen[i]);
    }
}

void Kernel::handleUserInput(char *input) {
    if (stringComparison(input, (char*) "HALT") == 0) {
        Screen::kprint((char*) "Halting the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (stringComparison(input, (char*) "PAGE") == 0) {
        uint32_t physicalAddress;
        uint32_t page = kmalloc(1000, 1, &physicalAddress);
        
        char pageHexString[16] = "";
        hexToString(page, pageHexString);

        char physicalAddressHexString[16] = "";
        hexToString(physicalAddress, physicalAddressHexString);
        
        Screen::kprint((char*) "Page: ");
        Screen::kprint(pageHexString);
        Screen::kprint((char*) ", physical address: ");
        Screen::kprint(physicalAddressHexString);
        Screen::kprint((char*) "\n");
    } else if (stringComparison(input, (char*) "SPLASH") == 0) {
        Kernel::printSplashScreen();
    } else if (stringComparison(input, (char*) "CLEAR") == 0) {
        Screen::clearScreen();
    } else if (stringComparison(input, (char*) "PANIC") == 0) {
        int result = 0 / 0;
        result++;
    } else {
        Screen::kprint(input);
        Screen::kprint((char*) "\n");
    }
    Screen::kprint((char*) "Panix:$ ");
}