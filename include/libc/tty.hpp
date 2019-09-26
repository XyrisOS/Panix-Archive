/**
 * @file tty.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
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