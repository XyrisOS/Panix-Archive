/**
 * File: kernel.cpp
 * Author: Keeton Feavel and James Osborne
 */

#ifndef KERNEL_H
#define KERNEL_H

#include "../cpu/idt/idt.h"
#include "../cpu/isr/isr.h"
#include "../cpu/ports/ports.h"
#include "../cpu/timer/timer.h"
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