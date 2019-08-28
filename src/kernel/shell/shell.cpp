#include <kernel/shell/shell.hpp>

shell::shell() {
    kprint("Loading kernel-level shell...\n");
    commandFunctions[0] = clearShell;
    commandFunctions[1] = help;
    commandFunctions[2] = panic;
    commandFunctions[3] = printSplash;
    commandFunctions[4] = panic; //panixkernel::Kernel::printTick;
    printShellIndicator();
}

void shell::handleShellInput(char* line) {
    // Loop through available commands and check if one
    // of them was inputted by the user.
    for (int i = 0; i < NUMBER_OF_COMMANDS; i++) {
        int j = strlen(line);
    }
}