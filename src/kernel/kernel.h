#ifndef KERNEL_H
#define KERNEL_H

#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

void handleUserInput(char *input);
void printSplashScreen();

#endif