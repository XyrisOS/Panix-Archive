/**
 * @file kernel.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
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
    kprint("Starting shell process...\n");
    RTC* rtc = (RTC*)DriverManager::activeDriverManager->getDriverWithTag("RTC");
    kprint("Shell got RTC.\n");
    // Print out the date at the shell start.
    kprintSetColor(LightCyan, Black);
    rtc->printTimeAndDate();
    kprintSetColor(White, Black);
    // Clear the screen and begin shell process
    //clearScreen();
    kprintSetColor(LightBlue, Black);
    // Make sure the kernel never dies!
    // kprint("Activating shell class...\n");
    Shell basch = Shell(DriverManager::activeDriverManager);
    // Mouse Interface Driver
    // kprint("Activating shell mouse...\n");
    ShellMouseEventHandler shellMouse;
    MouseDriver mouse(InterruptManager::activeInterruptManager, &shellMouse);
    DriverManager::activeDriverManager->addDriver(&mouse);
    // Keyboard Interface Driver
    // kprint("Activating shell keyboard...\n\n");
    ShellKeyboardEventHandler shellKeyboard;
    KeyboardDriver keyboard(InterruptManager::activeInterruptManager, &shellKeyboard);
    DriverManager::activeDriverManager->addDriver(&keyboard);
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

extern "C" void kernelMain(const void* multiboot_structure, uint32_t multiboot_magic) {
    // Clear screen, print welcome message.
    p_kernel_print_splash();
    // Initialize the Task Manager for Multitasking
    TaskManager taskManager = TaskManager();
    // Initialize the GDT, interrupt manager, and timer
    GlobalDescriptorTable gdt = GlobalDescriptorTable();
    InterruptManager interruptManager(0x20, &gdt, &taskManager);
    interruptManager.deactivate();

    /****************************
     * STAGE 1 - DYNAMIC MEMORY *
     ****************************/
    uint32_t* memupper = (uint32_t*)(((size_t)multiboot_structure) + 8);
    size_t heap = 10*1024*1024;
    MemoryManager memoryManager(heap, (*memupper)*1024 - heap - 10*1024);
    
    kprintSetColor(LightMagenta, Black);
    kprint("Heap 0x");
    kprintHex((heap >> 24) & 0xFF);
    kprintHex((heap >> 16) & 0xFF);
    kprintHex((heap >>  8) & 0xFF);
    kprintHex((heap      ) & 0xFF);
    
    void* allocated = memoryManager.malloc(1024);
    
    kprint("\nAllocated 0x");
    kprintHex((heap >> 24) & 0xFF);
    kprintHex((heap >> 16) & 0xFF);
    kprintHex((heap >>  8) & 0xFF);
    kprintHex((heap      ) & 0xFF);
    kprint("\n");
    kprintSetColor(White, Black);

    /*****************************************
     * STAGE 2 & 3 - LOAD & ACTIVATE DRIVERS *
     *****************************************/
    kprintSetColor(LightGreen, Black);
    kprint("Stage 2 - Loading Drivers...\n");
    kprintSetColor(White, Black);
    // Declare our driver manager
    DriverManager driverManager = DriverManager();
    // Mouse driver
    //MouseEventHandler mouseHandler;
    //MouseDriver mouse = MouseDriver(&interruptManager, &mouseHandler);
    //driverManager.addDriver(&mouse);
    // Keyboard driver
    KeyboardEventHandler keyboardHandler;
    KeyboardDriver keyboard = KeyboardDriver(&interruptManager, &keyboardHandler);
    driverManager.addDriver(&keyboard);
    // PC Beeper Driver
    Speaker speaker = Speaker();
    DriverManager::activeDriverManager->addDriver(&speaker);
    // Set the timer to operate at 60Hz
    Timer timer = Timer(&interruptManager, 60);
    DriverManager::activeDriverManager->addDriver(&timer);
    // Real Time Clock Driver
    RTC rtc = RTC(&interruptManager);
    DriverManager::activeDriverManager->addDriver(&rtc);
    // PCI Interface Driver
    PeripheralComponentInterconnectController PCIController;
    PCIController.selectDrivers(&driverManager, &interruptManager);
    // For whatever reason we *have* to also activate the drivers in this function or it doesn't work at all.
    // I'm wondering if this has something to do with multitasking or if something is wrong with the driver
    // manager. I'm really not sure...
    kprintSetColor(LightGreen, Black);
    kprint("Stage 3 - Activating Drivers...\n");
    kprintSetColor(White, Black);
    driverManager.activateAll();

    // If we put all of the code in startShellAsProcess here then it works.
    // But if we make the call to it here then it doesn't.

    /*********************************
     * STAGE 4 - ACTIVATE INTERRUPTS *
     *********************************/
    // Activate our interrupt manager
    kprintSetColor(LightGreen, Black);
    kprint("Stage 4 - Activating Interrupts...\n");
    kprintSetColor(White, Black);
    interruptManager.activate();
    // Sleep so we can debug the logs thus far
    // FIXME: For whatever reason we never wake back up after calling this.
    kprintSetColor(LightRed, Black);
    Timer* sleepTimer = (Timer*)driverManager.getDriverWithTag("PIT");
    sleepTimer->sleep(60*5);
    kprintSetColor(White, Black);

    /*****************************
     * STAGE 5 - START PROCESSES *
     *****************************/
    // Activate processes
    kprintSetColor(LightGreen, Black);
    kprint("Stage 5 - Starting shell process...\n");
    kprintSetColor(White, Black);
    // Begin multitasking example
    Task baschTask(&gdt, startShellAsProcess);
    taskManager.addTask(&baschTask);

    // Setup VGA desktops
    // Desktop* desktop = p_kernel_gui_init();
    while (1) {
        // Keep the kernel alive
        //desktop->draw(&vga);
    }
    
    // Return control back to loader.s to cli & hlt.
    return;
}

Desktop* p_kernel_gui_init() {
    // Create a desktop environment
    Desktop desktop(320, 200, 0x00,0x00,0xA8);
    VideoGraphicsArray vga;
    MouseDriver* mouse = (MouseDriver*)DriverManager::activeDriverManager->getDriverWithTag("MOUSE");
    KeyboardDriver* keyboard = (KeyboardDriver*)DriverManager::activeDriverManager->getDriverWithTag("KEYBOARD");
    mouse->setHandler(&desktop);
    keyboard->setHandler(&desktop);
    vga.setMode(320, 200, 8);
    vga.fillRect(0, 0, 320, 200, 0x00, 0x00, 0xA8);
    vga.setMode(320,200, 8);
    Window win1(&desktop, 10,10,20,20, 0xA8,0x00,0x00);
    desktop.addChild(&win1);
    Window win2(&desktop, 40,15,30,30, 0x00,0xA8,0x00);
    desktop.addChild(&win2);
    // FIXME: warning: address of local variable ‘desktop’ returned [-Wreturn-local-addr]
    return &desktop;
}

void p_kernel_print_splash() {
    clearScreen();
    kprintSetColor(Yellow, Black);
    kprint("Welcome to Panix\n");
    kprint("Developed by graduates and undergraduates of Cedarville University.\n");
    kprint("Copyright Keeton Feavel et al (c) 2019. All rights reserved.\n\n");
    kprintSetColor(White, Black);
}