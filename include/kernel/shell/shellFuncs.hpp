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

void panic();

void printSplash();

void vgaStart();

#endif /* PANIX_SHELLFUNCS_HPP */