#include <kernel/shell/shellFuncs.hpp>

void printShellIndicator() {
    kprint("basch#");
}

void clearShell() {
    clearScreen();
}

void help() {
    kprint("Baschel Fortner - The Panix Kernel Level Shell\n");
    kprint("Version: 0.1 - Build: m08d28y19\n");
    // I can't get these functions to work in the shell object for
    // whatever reason. And because the shell commands are private
    // I can't access them from here. So I'll have to come back to
    // this at another time.
    /*
    for (auto commandName : commandNames) {
        kprint(commandName);
        kprint("\n");
    }
    */
}

void panic() {
    // This is here to demonstrate the panic screen when implemented.
    int result = 0 / 0;
    result++;
}

void printSplash() {
    kprint("\n\nWelcome to Panix!\n\n");
}

void vgaStart() {
    // Initialize the VGA driver
    VideoGraphicsArray vga;
    vga.setMode(320,200,8);
    for(int32_t y = 0; y < 200; y++) {
        for(int32_t x = 0; x < 320; x++) {
            vga.setPixel(x, y, 0x00, 0x00, 0xA8);
        }
    }
}

void exit() {
    kprint("You can't exit the shell! It's part of the kernel!");
}