//  Main function for the EDIX kernel.
//  kernel.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "kprint.h"

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
extern "C" void kMain(void* multiboot_structure, unsigned int magicnumber) {
    // Print welcome to kernel
    kprint("Welcome to EDIX.\n");
    // Create loop to keep kernel alive
    while(1);
}
