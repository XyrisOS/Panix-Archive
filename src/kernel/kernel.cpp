
#include <kernel/kernel.hpp>

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/) {
    // Clear screen, print welcome message.
    clearScreen();
    printf("Welcome to Panix\n");
    printf("Developed by graduates and undergraduates of Cedarville University.\n");
    printf("Copyright Keeton Feavel et al (c) 2019. All rights reserved.\n\n");
    // Initialize the GDT and interrupt manager
    GlobalDescriptorTable gdt;
    InterruptManager interruptManager(0x20, &gdt);

    printf("Initializing Hardware, Stage 1\n");
    // Declare our driver manager
    DriverManager driverManager;
    
    /*************************************************
     * DO NOT SWITCH THE ORDER OF ADDING THESE DRIVERS 
     *************************************************/
    MouseEventHandler mouseEventHandler;
    MouseDriver mouse(&interruptManager, &mouseEventHandler);
    driverManager.addDriver(&mouse);

    KeyboardEventHandler keyboardEventHandler;
    KeyboardDriver keyboard(&interruptManager, &keyboardEventHandler);
    driverManager.addDriver(&keyboard);
    // Activate all the drivers we just added
    printf("Initializing Hardware, Stage 2\n");
    driverManager.activateAll();
    // Activate our interrupt manager
    printf("Initializing Hardware, Stage 3\n");
    interruptManager.activate();
    // Make sure the kernel never dies!
    while(1);
}
