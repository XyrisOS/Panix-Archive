
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
    kprint("Welcome to Panix\n");
    kprint("Developed by graduates and undergraduates of Cedarville University.\n");
    kprint("Copyright Keeton Feavel et al (c) 2019. All rights reserved.\n\n");
    // Initialize the GDT and interrupt manager
    GlobalDescriptorTable gdt;
    InterruptManager interruptManager(0x20, &gdt);

    kprint("Initializing Hardware, Stage 1 - Loading Drivers...\n");
    // Declare our driver manager
    DriverManager driverManager;
    
    /*************************************************
     * DO NOT SWITCH THE ORDER OF ADDING THESE DRIVERS 
     *************************************************/
    // Mouse Interface Driver
    MouseEventHandler mouseEventHandler;
    MouseDriver mouse(&interruptManager, &mouseEventHandler);
    driverManager.addDriver(&mouse);
    // Keyboard Interface Driver
    KeyboardEventHandler keyboardEventHandler;
    KeyboardDriver keyboard(&interruptManager, &keyboardEventHandler);
    driverManager.addDriver(&keyboard);
    // PCI Interface Driver
    PeripheralComponentInterconnectController PCIController;
    PCIController.SelectDrivers(&driverManager, &interruptManager);
    // Activate all the drivers we just added
    kprint("Initializing Hardware, Stage 2 - Activating Drivers...\n");
    driverManager.activateAll();
    // Activate our interrupt manager
    kprint("Initializing Hardware, Stage 3 - Activating Interrupts...\n");
    interruptManager.activate();
    // Make sure the kernel never dies!
    shell basch = shell();
    while(1);
}
