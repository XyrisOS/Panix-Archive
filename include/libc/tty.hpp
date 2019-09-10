#ifndef PANIX_TTY_HPP
#define PANIX_TTY_HPP

#include <libc/kprint.hpp>

/**
 * @brief Clears the kernel console.
 * 
 */
void clearScreen();

/**
 * @brief Prints a dead cow ASCII art for the panic screen
 * 
 */
void printPanicScreen();

#endif /* PANIX_TTY_HPP */