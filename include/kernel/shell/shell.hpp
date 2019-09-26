/**
 * @file shell.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_SHELL_HPP
#define PANIX_SHELL_HPP

#include <kernel/shell/shellFuncs.hpp>
#include <libc/kprint.hpp>
#include <libc/string.hpp>
#include <libc/tty.hpp>
// Number of commands available to the shell
#define NUMBER_OF_COMMANDS 5

class Shell {
    private:
        const char commandNames[NUMBER_OF_COMMANDS][16] = {
            "clear",
            "help",
            "time",
            "splash",
            "vga"
        };
        void (*commandFunctions[NUMBER_OF_COMMANDS])();

    public:
        /**
         * @brief Construct a new shell object
         * 
         */
        Shell();
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

#endif /* PANIX_SHELL_HPP */