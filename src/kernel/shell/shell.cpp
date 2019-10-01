/**
 * @file shell.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <kernel/shell/shell.hpp>

Shell::Shell(InterruptManager* interruptManager, DriverManager* driverManager) {
    commandFunctions[0] = &Shell::clearShell;
    commandFunctions[1] = &Shell::help;
    commandFunctions[2] = &Shell::printTime;
    commandFunctions[3] = &Shell::printSplash;
    commandFunctions[4] = &Shell::vgaStart; //panixkernel::Kernel::printTick;
}

void Shell::handleShellInput(char* line) {
    // Loop through available commands and check if one
    // of them was inputted by the user.
    bool foundCommand = false;
    for (int i = 0; i < NUMBER_OF_COMMANDS; i++) {
        if (strcmp((char*) commandNames[i], line) == 0) {
            // WHAT THE ACTUAL FRICK IS THIS SYNTAX C++???
            // Credit to Micah for figuring out this awful mess
            (this->*(commandFunctions[i]))();
            foundCommand = true;
            break;
        }
    }
    if (strcmp((char*)"shutdown", line) == 0) {
        clearScreen();
        kprint("It's now safe to turn off your computer.\n");
        isTerminated = true;
        return;
    }
    // strcmp will return "false" (0) if they're the same so anything else is true
    if (foundCommand == false && (strcmp("", line) != 0)) {
        kprint("Command does not exist.\n");
    }
    printShellIndicator();
}

void Shell::activate() {
    printShellIndicator();
}

void Shell::printShellIndicator() {
    kprintSetColor(LightRed, Black);
    kprint("basch#");
    kprintSetColor(White, Black);
}

void Shell::clearShell() {
    clearScreen();
}

void Shell::help() {
    kprint("Baschel Fortner - The Panix Kernel Level Shell\n");
    kprint("Version: 0.1 - Build: 290919a\n");
    // I can't get these functions to work in the shell object for
    // whatever reason. And because the shell commands are private
    // I can't access them from here. So I'll have to come back to
    // this at another time.
    for (auto commandName : commandNames) {
        kprint(commandName);
        kprint("\n");
    }
}

void Shell::printSplash() {
    clearScreen();
    kprintSetColor(Yellow, Black);
    kprint("Welcome to Panix\n");
    kprint("Developed by graduates and undergraduates of Cedarville University.\n");
    kprint("Copyright Keeton Feavel et al (c) 2019. All rights reserved.\n\n");
    kprintSetColor(White, Black);
}

void Shell::printTime() {
    kprint("Coming soon.\n");
}

void Shell::vgaStart() {
    // Initialize the VGA driver
    VideoGraphicsArray vga;
    vga.setMode(320, 200, 8);
    vga.fillRect(0, 0, 320, 200, 0x00, 0x00, 0xA8);
}