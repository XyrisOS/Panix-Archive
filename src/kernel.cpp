//  Main function for the EDIX kernel.
//  kernel.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "types.h"
#include "gdt.h"
#include "port.h"
#include "interrupts.h"
#include "kprint.h"
#include "termcolor.h"

typedef void (*constructor)();
extern "C" constructor constructor_start;
extern "C" constructor constructor_end;

/**
 * Constructor call for the EDIX kernel.
 */
extern "C" void callConstructors() {
    for (constructor * i = &constructor_start; i != &constructor_end; i++) {
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
    kprint("Created by undergraduates of Cedarville University.\n");
    kprint("(c) Solar Pepper Studios 2018, all rights reserved.\n\n");
    kprint("Welcome to \n\n");
    
    // Print the ASCII EDIX art for the cool effect
    kprint("d88888b d8888b. d888888b db    db \n");
    kprint("88'     88  `8D   `88'   `8b  d8' \n");
    kprint("88ooooo 88   88    88     `8bd8'  \n");
    kprint("88~~~~~ 88   88    88     .dPYb.  \n");
    kprint("88.     88  .8D   .88.   .8P  Y8. \n");
    kprint("Y88888P Y8888D' Y888888P YP    YP \n\n");
    
    // Instantiate the GDT, IDT, and activate interrupt
    GlobalDescriptorTable gdt;
    InterruptManager interrupts(0x20, &gdt);
    interrupts.activate();

    // Create loop to keep kernel alive
    while (1) {
        //
    }
}