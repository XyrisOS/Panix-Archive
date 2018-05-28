//  Main function for the EDIX kernel.
//  kernel.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "types.h"
#include "gdt.h"
#include "port.h"
#include "kprint.h"
#include "termcolor.h"
#include "interrupts.h"

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
 * @param multiboot_structure - Multiboot structure from GRUB.
 * @param magicnumber - Magicnumber from loader.s
 */
extern "C" void kernel(void * multiboot_structure, uint32_t magicnumber) {
    //Clear the terminal
    kprint_clear();
    color_foreground fore; // Foreground color
    color_background bkg; // Background color
    // Print welcome to kernel and copyright information
    kprint(" Created by undergraduates of Cedarville University.\n");
    kprint(" (c) Solar Pepper Studios 2018, all rights reserved.\n\n");
    kprint(" Welcome to ");
    kprint_c(" EDIX \n\n", fore.black, bkg.white);
    kprint(" EDIX -> EDICS\n");
    kprint(" EDICS: Educational Information Computation System\n\n");

    // Instantiate the GDT
    GlobalDescriptorTable gdt;

    // Create loop to keep kernel alive
    while (1) {
        //
    }
}
