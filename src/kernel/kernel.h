#ifndef KERNEL_H
#define KERNEL_H

#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/screen/screen.h"

/**
 * @brief 
 * 
 * @param input 
 */
void handleUserInput(char *input);

/**
 * @brief 
 * 
 */
void printSplashScreen();

#endif