#include <kernel/shell/shell.hpp>

shell::shell() {
    commandFunctions[0] = clearShell;
    commandFunctions[1] = help;
    commandFunctions[2] = panic;
    commandFunctions[3] = printSplash;
    commandFunctions[4] = panic; //panixkernel::Kernel::printTick;
}

void shell::handleShellInput(char* line) {
    // Loop through available commands and check if one
    // of them was inputted by the user.
    for (int i = 0; i < NUMBER_OF_COMMANDS; i++) {
        int j = strlen(line);
    }
}

void shell::printShellIndicator() {
    kprint("basch#");
}

void shell::clearShell() {
    clearScreen();
}

void shell::help() {
    kprint("Baschel Fortner - The Panix Kernel Level Shell\n");
    kprint("Version: 0.1 - Build: m08d28y19");
    for (auto commandName : commandNames) {
        kprint(commandName);
        kprint("\n");
    }
}

void shell::panic() {
    // This is here to demonstrate the panic screen when implemented.
    int result = 0 / 0;
    result++;
}

void shell::printSplash() {
    kprint("\n\nWelcome to Panix!\n\n");
}

void shell::exit() {
    kprint("You can't exit the shell! It's part of the kernel!");
}