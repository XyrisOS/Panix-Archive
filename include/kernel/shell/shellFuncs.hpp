/**
 * @file shellFuncs.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_SHELLFUNCS_HPP
#define PANIX_SHELLFUNCS_HPP

#include <kernel/shell/shell.hpp>
#include <libc/kprint.hpp>
#include <libc/string.hpp>
#include <libc/tty.hpp>
#include <drivers/vga/VGA.hpp>

/**
 * @brief Prints the indicator for the shell.
 * 
 */
void printShellIndicator();

void clearShell();

void help();

void printSplash();

void printTime();

void vgaStart();

#endif /* PANIX_SHELLFUNCS_HPP */