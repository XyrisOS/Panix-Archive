/**
 * @file kernel.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <kernel/kernel.hpp>

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

void startShellAsProcess() {
    // Clear the screen and begin shell process
    //clearScreen();
    kprintSetColor(LightBlue, Black);
    // Make sure the kernel never dies!
    kprint("Activating shell class...\n");
    Shell basch = Shell(kernelInterruptManager, kernelDriverManager);
    // Mouse Interface Driver
    kprint("Activating shell mouse...\n");
    ShellMouseEventHandler shellMouse;
    MouseDriver mouse(kernelInterruptManager, &shellMouse);
    kernelDriverManager->addDriver(&mouse);
    // Keyboard Interface Driver
    kprint("Activating shell keyboard...\n");
    ShellKeyboardEventHandler shellKeyboard;
    KeyboardDriver keyboard(kernelInterruptManager, &shellKeyboard);
    kernelDriverManager->addDriver(&keyboard);
    // Tell the keyboard to use this shell
    kprintSetColor(White, Black);
    shellKeyboard.setConsole(&basch);
    // Activate the shell
    basch.activate();
    while (!basch.isTerminated) {
        // Do nothing
    }
    // Jump back out once the shell is done.
    return;
}

extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/) {
    // Clear screen, print welcome message.
    clearScreen();
    kprintSetColor(Yellow, Black);
    kprint("Welcome to Panix\n");
    kprint("Developed by graduates and undergraduates of Cedarville University.\n");
    kprint("Copyright Keeton Feavel et al (c) 2019. All rights reserved.\n\n");
    
    // Initialize the Task Manager for Multitasking
    TaskManager taskManager;
    // Initialize the GDT, interrupt manager, and timer
    GlobalDescriptorTable gdt;
    InterruptManager interruptManager(0x20, &gdt, &taskManager);
    interruptManager.deactivate();

    /**************************
     * STAGE 1 - LOAD DRIVERS *
     **************************/
    kprintSetColor(LightGreen, Black);
    kprint("Stage 1 - Loading Drivers...\n");
    kprintSetColor(White, Black);
    // Declare our driver manager
    DriverManager driverManager;
    // Set pointers to all of the managers
    kernelDriverManager = &driverManager;
    kernelTaskManager = &taskManager;
    kernelInterruptManager = &interruptManager;
    // PC Beeper Driver
    Speaker speaker = Speaker();
    driverManager.addDriver(&speaker);
    // Set the timer to operate at 60Hz
    Timer timer = Timer(&interruptManager, 60);
    driverManager.addDriver(&timer);
    // Real Time Clock Driver
    RTC rtc = RTC();
    driverManager.addDriver(&rtc);
    // PCI Interface Driver
    PeripheralComponentInterconnectController PCIController;
    PCIController.SelectDrivers(&driverManager, &interruptManager);

    // If we put all of the code in startShellAsProcess here then it works.
    // But if we make the call to it here then it doesn't.

    /******************************
     * STAGE 2 - ACTIVATE DRIVERS *
     ******************************/
    // Activate all the drivers we just added
    kprintSetColor(LightGreen, Black);
    kprint("Stage 2 - Activating Drivers...\n");
    kprintSetColor(White, Black);
    driverManager.activateAll();

    /*********************************
     * STAGE 3 - ACTIVATE INTERRUPTS *
     *********************************/
    // Activate our interrupt manager
    kprintSetColor(LightGreen, Black);
    kprint("Stage 3 - Activating Interrupts...\n");
    kprintSetColor(White, Black);
    interruptManager.activate();
    kprintSetColor(LightCyan, Black);
    rtc.printTimeAndDate();
    kprintSetColor(White, Black);

    /*****************************
     * STAGE 4 - START PROCESSES *
     *****************************/
    // Activate processes
    kprintSetColor(LightGreen, Black);
    kprint("Stage 4 - Starting shell process...\n");
    kprintSetColor(White, Black);
    // Begin multitasking example
    Task baschTask(&gdt, startShellAsProcess);
    taskManager.addTask(&baschTask);

    // Setup VGA desktops
    /*
    // Create a desktop environment
    Desktop desktop(320, 200, 0x00,0x00,0xA8);
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
    while (1) {
        // Keep the kernel alive
        //desktop.Draw(&vga);
    }

    // Return control back to loader.s to cli & hlt.
    return;
}
