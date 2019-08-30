#include <kernel/shell/shell.hpp>

shell::shell() {
    commandFunctions[0] = clearShell;
    commandFunctions[1] = help;
    commandFunctions[2] = panic;
    commandFunctions[3] = printSplash;
    commandFunctions[4] = vgaStart; //panixkernel::Kernel::printTick;
    printShellIndicator();
}

void shell::handleShellInput(char* line) {
    // Loop through available commands and check if one
    // of them was inputted by the user.
    for (int i = 0; i < NUMBER_OF_COMMANDS; i++) {
        if (strcmp((char*) commandNames[i], line) == 0) {
            (*commandFunctions[i])();
            break;
        }
    }
    printShellIndicator();
}