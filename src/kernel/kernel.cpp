
#include <kernel/kernel.hpp>

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    // Clear screen, print welcome message.
    clearScreen();
    printf("Panix\n");

    GlobalDescriptorTable gdt;
    InterruptManager interruptManager(0x20, &gdt);

    printf("Initializing Hardware, Stage 1\n");
    
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

    printf("Initializing Hardware, Stage 2\n");
    driverManager.activateAll();
        
    printf("Initializing Hardware, Stage 3\n");
    interruptManager.activate();

    while(1);
}
