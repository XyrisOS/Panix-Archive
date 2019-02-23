/**
 * File: kernel.cpp
 * Author: Keeton Feavel and James Osborne
 * 
 * Panix kernel main source file.
 * Includes the kernel's main() function
 * that helps make the jump from 16-bit
 * real mode out of assembly and into the
 * 32-bit protected mode where out kernel
 * will be executing.
 */

#include "kernel.h"

/**
 *     ____  ___    _   _______  __
 *    / __ \/   |  / | / /  _/ |/ /
 *   / /_/ / /| | /  |/ // / |   / 
 *  / ____/ ___ |/ /|  // / /   |  
 * /_/   /_/  |_/_/ |_/___//_/|_|  
 *                          
 * Panix kernel main function. Called in kernel_entry.asm
 * Executed prior to bootloader code in boot32.asm
 */
extern "C" int kernelMain() {
    isrInstall();
    irqInstall();

    printSplashScreen();

    return 0;
}

void printSplashScreen() {
    clearScreen();
    char* splashScreen[] = {
        (char*) "     ____  ___    _   _______  __ \n",
        (char*) "    / __ \\/   |  / | / /  _/ |/ /\n",
        (char*) "   / /_/ / /| | /  |/ // / |   /  \n",
        (char*) "  / ____/ ___ |/ /|  // / /   |   \n",
        (char*) " /_/   /_/  |_/_/ |_/___//_/|_|   \n",
        (char*) "\nWelcome to the PANIX kernel!\n",
        (char*) "\nType HALT to halt the CPU\n> "
    };
    for (int i = 0; i < 7; i++) {
        kprint(splashScreen[i]);
    }
}

void handleUserInput(char *input) {
    if (stringComparison(input, (char*) "HALT") == 0) {
        kprint((char*) "Halting the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (stringComparison(input, (char*) "PAGE") == 0) {
        uint32_t physicalAddress;
        uint32_t page = kmalloc(1000, 1, &physicalAddress);
        
        char pageHexString[16] = "";
        hexToString(page, pageHexString);

        char physicalAddressHexString[16] = "";
        hexToString(physicalAddress, physicalAddressHexString);
        
        kprint((char*) "Page: ");
        kprint(pageHexString);
        kprint((char*) ", physical address: ");
        kprint(physicalAddressHexString);
        kprint((char*) "\n");
    }
    //kprint((char*) "You said: ");
    kprint(input);
    kprint((char*) "\nPanix:~$ ");
}