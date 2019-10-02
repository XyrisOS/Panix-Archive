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

Shell::Shell(DriverManager* driverManager) {
    commandFunctions[0] = &Shell::clearShell;
    commandFunctions[1] = &Shell::help;
    commandFunctions[2] = &Shell::printTime;
    commandFunctions[3] = &Shell::printSplash;
    commandFunctions[4] = &Shell::vgaStart;
    commandFunctions[5] = &Shell::printTick;
    commandFunctions[6] = &Shell::callShutdown;
    commandFunctions[7] = &Shell::callReboot;
    this->driverManager = driverManager;
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
    kprint("basch# ");
    kprintSetColor(White, Black);
}

void Shell::clearShell() {
    clearScreen();
}

void Shell::help() {
    kprint("Baschel Fortner - The Panix Kernel Level Shell\n");
    kprint("Version: 0.1 - Build: 290919a\n\n");
    // I can't get these functions to work in the shell object for
    // whatever reason. And because the shell commands are private
    // I can't access them from here. So I'll have to come back to
    // this at another time.
    kprintSetColor(LightGreen, Black);
    for (auto commandName : commandNames) {
        kprint(commandName);
        kprint("\n");
    }
    kprint("\n");
    kprintSetColor(White, Black);
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
    RTC* rtc = (RTC*)driverManager->getDriverWithTag("RTC");
    rtc->printTimeAndDate();
}

void Shell::printTick() {
    Timer* timer = (Timer*)driverManager->getDriverWithTag("TIMER");
    timer->printTick();
}

void Shell::vgaStart() {
    // Initialize the VGA driver
    VideoGraphicsArray vga;
    vga.setMode(320, 200, 8);
    vga.fillRect(0, 0, 320, 200, 0x00, 0x00, 0xA8);
}

void Shell::callShutdown() {
    shutdown();
    isTerminated = true;
}

void Shell::callReboot() {
    reboot();
    isTerminated = true;
}