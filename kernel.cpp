//  Main function for the EDIX kernel.
//  kernel.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "types.h"
#include "kprint.h"
#include "termcolor.h"

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

/**
 * Constructor call for the EDIX kernel.
 */
extern "C" void callConstructors() {
    for (constructor * i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

/**
 * Main function for the EDIX kernel.
 * void * multiboot_structure - Multiboot structure from GRUB.
 * unsigned int magicnumber - Magicnumber from loader.s
 */
extern "C" void kMain(void* multiboot_structure, uint32_t magicnumber) {
    //Clear the terminal
    kprint_clear();
    color_foreground fore; // Foreground color
    color_background back; // Background color
    // Print welcome to kernel
    kprint("Created by undergraduates of Cedarville University.\n");
    kprint("Welcome to ");
    kprint_c(" EDIX \n", fore.black, back.white);
    kprint_c("Color test.\n", fore.light_green, back.black);
    kprint_error("This is an error.\n");
    // Create loop to keep kernel alive
    while(1);
}
