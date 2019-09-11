#include <kernel/shell/shellFuncs.hpp>

void printShellIndicator() {
    kprint("basch#");
}

void clearShell() {
    clearScreen();
}

void help() {
    kprint("Baschel Fortner - The Panix Kernel Level Shell\n");
    kprint("Version: 0.1 - Build: m09d10y19\n");
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
    vga.setMode(320, 200, 8);
    vga.fillRect(0, 0, 320, 200, 0x00, 0x00, 0xA8);
}