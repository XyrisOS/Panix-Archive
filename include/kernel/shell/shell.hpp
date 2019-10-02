/**
 * @file shell.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_SHELL_HPP
#define PANIX_SHELL_HPP

#include <cpu/power/Power.hpp>
#include <drivers/DriverManager.hpp>
#include <drivers/timer/Timer.hpp>
#include <drivers/rtc/RTC.hpp>
#include <drivers/vga/VGA.hpp>
#include <libc/stdio.hpp>
#include <libc/kprint.hpp>
#include <libc/string.hpp>
#include <libc/tty.hpp>

// Number of commands available to the shell
#define NUMBER_OF_COMMANDS 8

class Shell {
    private:
        DriverManager* driverManager;
        const char commandNames[NUMBER_OF_COMMANDS][16] = {
            "clear",
            "help",
            "time",
            "splash",
            "vga",
            "tick",
            "shutdown",
            "reboot"
        };
        void (Shell::*commandFunctions[NUMBER_OF_COMMANDS])();
        // Available commands
        void printShellIndicator();
        void clearShell();
        void help();
        void printSplash();
        void printTime();
        void vgaStart();
        void printTick();
        void callShutdown();
        void callReboot();

    public:
        /**
         * @brief Construct a new shell object
         * 
         */
        Shell(DriverManager* driverManager);
        /**
         * @brief Processes the user keyboard input passed in from the
         * keyboard event handler.
         * 
         * @param line User input. Should include the '\n' character
         */
        void handleShellInput(char* line);
        /**
         * @brief Prints out the shell indicator to inform the user that the
         * shell is now ready to recieve input.
         * 
         */
        void activate();
        /**
         * @brief Boolean value which signals if the user has enterd a command
         * which should exit the shell / kernel (i.e. exit, logout, etc.)
         * 
         */
        bool isTerminated;
};

#endif /* PANIX_SHELL_HPP */