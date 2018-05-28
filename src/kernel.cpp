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

// May not be necessary. Here to try to get interrupts to print.
void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;
    
    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }
        
        if(x >= 80)
        {
            x = 0;
            y++;
        }
        
        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

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
    kprint(" Created by undergraduates of Cedarville University.\n");
    kprint(" (c) Solar Pepper Studios 2018, all rights reserved.\n\n");
    kprint(" Welcome to ");
    kprint_c(" EDIX \n\n", fore.black, bkg.white);

    // Instantiate the GDT, IDT, and activate interrupt
    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);
    interrupts.activate();

    // Create loop to keep kernel alive
    while (1) {
        //
    }
}