#ifndef SHELL_HPP
#define SHELL_HPP
#include <libc/printf.hpp>
#include <libc/string.h>
// Number of commands available to the shell
#define NUMBER_OF_COMMANDS 5

class shell {
    private:
        const char commandNames[NUMBER_OF_COMMANDS][16] = {
            "clear",
            "help",
            "panic",
            "splash",
            "tick"
        };
    public:
        /**
         * @brief Processes the user keyboard input passed in from the
         * keyboard event handler.
         * 
         * @param line User input. Should include the '\n' character
         */
        void handleShellInput(char* line);
        /**
         * @brief Boolean value which signals if the user has enterd a command
         * which should exit the shell / kernel (i.e. exit, logout, etc.)
         * 
         */
        bool isTerminated;
};

#endif /* SHELL_HPP */