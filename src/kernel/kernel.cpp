
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
    kprintSetColor(Yellow, Black);
    kprint("Welcome to Panix\n");
    kprint("Developed by graduates and undergraduates of Cedarville University.\n");
    kprint("Copyright Keeton Feavel et al (c) 2019. All rights reserved.\n\n");
    // Initialize the GDT, interrupt manager, and timer
    GlobalDescriptorTable gdt;
    InterruptManager interruptManager(0x20, &gdt);
    interruptManager.deactivate();
    kprintSetColor(Red, Black);
    kprint("Stage 1 - Loading Drivers...\n");
    kprintSetColor(White, Black);
    // Declare our driver manager
    DriverManager driverManager;
    // Create a desktop environment
    Desktop desktop(320, 200, 0x00,0x00,0xA8);
    
    /*************************************************
     * DO NOT SWITCH THE ORDER OF ADDING THESE DRIVERS 
     *************************************************/
    // Mouse Interface Driver
    ShellMouseEventHandler shellMouse;
    MouseDriver mouse(&interruptManager, &shellMouse);
    driverManager.addDriver(&mouse);
    // Keyboard Interface Driver
    ShellKeyboardEventHandler shellKeyboard;
    KeyboardDriver keyboard(&interruptManager, &shellKeyboard);
    driverManager.addDriver(&keyboard);
    // PC Beeper Driver
    Speaker speaker = Speaker();
    driverManager.addDriver(&speaker);
    // Set the timer to operate at 60Hz
    Timer timer = Timer(60);
    driverManager.addDriver(&timer);
    // Real Time Clock Driver
    RTC rtc = RTC();
    driverManager.addDriver(&rtc);
    // PCI Interface Driver
    PeripheralComponentInterconnectController PCIController;
    PCIController.SelectDrivers(&driverManager, &interruptManager);
    // Activate all the drivers we just added
    kprintSetColor(Red, Black);
    kprint("Stage 2 - Activating Drivers...\n");
    kprintSetColor(White, Black);
    driverManager.activateAll();
    // Activate our interrupt manager
    kprintSetColor(Red, Black);
    kprint("Stage 3 - Activating Interrupts...\n");
    kprintSetColor(White, Black);
    interruptManager.setInterruptManagerTimer(&timer);
    interruptManager.activate();
    kprintSetColor(LightCyan, Black);
    rtc.printTimeAndDate();
    kprintSetColor(White, Black);
    
    // Make sure the kernel never dies!
    shell basch = shell();
    // Tell the shell keyboard handler where the shell is.
    shellKeyboard.setConsole(&basch);
    // Setup VGA desktops
    /*
    VideoGraphicsArray vga;
    mouse.setHandler(&desktop);
    keyboard.setHandler(&desktop);
    vga.setMode(320, 200, 8);
    vga.fillRect(0, 0, 320, 200, 0x00, 0x00, 0xA8);
    vga.setMode(320,200, 8);
    Window win1(&desktop, 10,10,20,20, 0xA8,0x00,0x00);
    desktop.addChild(&win1);
    Window win2(&desktop, 40,15,30,30, 0x00,0xA8,0x00);
    desktop.addChild(&win2);
    */
    while (1) { //(!basch.isTerminated) {
        // Keep the kernel alive
        //desktop.Draw(&vga);
    }
    // Return control back to loader.s to cli & hlt.
    return;
}
