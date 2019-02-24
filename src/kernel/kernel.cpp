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
inline drivers::Screen screen;
inline panixkernel::Kernel kernel;

/**
 * @brief Main entry point for the kernel
 * 
 */
extern "C" int kernelMain() {
    cpu::ISR::isrInstall();
    cpu::ISR::irqInstall();

    kernel.printSplashScreen();
    screen.kprint((char*) "Panix:$ ");

    return 0;
}

/*******************
* Public Functions *
********************/
void panixkernel::Kernel::printSplashScreen() {
    screen.clearScreen();
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
        screen.kprint(splashScreen[i]);
    }
}

void panixkernel::Kernel::handleUserInput(char* input) {
    if (stringComparison(input, (char*) "HALT") == 0) {
        screen.kprint((char*) "Halting the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (stringComparison(input, (char*) "PAGE") == 0) {
        uint32_t physicalAddress;
        uint32_t page = kmalloc(1000, 1, &physicalAddress);
        
        char pageHexString[16] = "";
        hexToString(page, pageHexString);

        char physicalAddressHexString[16] = "";
        hexToString(physicalAddress, physicalAddressHexString);
        
        screen.kprint((char*) "Page: ");
        screen.kprint(pageHexString);
        screen.kprint((char*) ", physical address: ");
        screen.kprint(physicalAddressHexString);
        screen.kprint((char*) "\n");
    } else if (stringComparison(input, (char*) "TICK") == 0) {
        timer.printTick();
    } else if (stringComparison(input, (char*) "SPLASH") == 0) {
        this->printSplashScreen();
    } else if (stringComparison(input, (char*) "CLEAR") == 0) {
        screen.clearScreen();
    } else if (stringComparison(input, (char*) "PANIC") == 0) {
        int result = 0 / 0;
        result++;
    } else {
        screen.kprint(input);
        screen.kprint((char*) "\n");
    }
    screen.kprint((char*) "Panix:$ ");
}