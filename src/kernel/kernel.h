#ifndef KERNEL_H
#define KERNEL_H

#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

/**
 * @brief Handles all keyboard input for the basic kernel shell.
 * 
 * @param input String input from keyboard to be processed.
 */
void handleUserInput(char *input);

/**
 * @brief Prints the Panix splash screen on boot.
 * 
 */
void printSplashScreen();

#endif