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

#include "../drivers/ports.h"
#include "../drivers/screen.h"

/** 
 * This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 
 */
void entryTest() {
    kprint("Panix has panicked! Kernel jumped to invalid start funtion.\n");
}

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
int main() {
    clear_screen();
    char splashScreen [6][36] = {
        "     ____  ___    _   _______  __ \n",
        "    / __ \\/   |  / | / /  _/ |/ /\n",
        "   / /_/ / /| | /  |/ // / |   /  \n",
        "  / ____/ ___ |/ /|  // / /   |   \n",
        " /_/   /_/  |_/_/ |_/___//_/|_|   \n",
        "\nWelcome to the PANIX kernel!\n"
    };
    for (int i = 0; i < 6; i++) {
        kprint(splashScreen[i]);
    }
   /* Fill up the screen */

    while (1) {
        // Keep kernel running
    }
    return 0;
}
