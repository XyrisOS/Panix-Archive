#include <kernel/shell/shell.hpp>

Shell::Shell() {
    commandFunctions[0] = clearShell;
    commandFunctions[1] = help;
    commandFunctions[2] = printTime;
    commandFunctions[3] = printSplash;
    commandFunctions[4] = vgaStart; //panixkernel::Kernel::printTick;
    printShellIndicator();
}

void Shell::handleShellInput(char* line) {
    // Loop through available commands and check if one
    // of them was inputted by the user.
    bool foundCommand = false;
    for (int i = 0; i < NUMBER_OF_COMMANDS; i++) {
        if (strcmp((char*) commandNames[i], line) == 0) {
            (*commandFunctions[i])();
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