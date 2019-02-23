#ifndef TIMER_H
#define TIMER_H

#include "../drivers/screen.h"
#include "../libc/string.h"
#include "isr.h"
#include "ports.h"
#include "type.h"

//TODO: There are ways to get the CPU frequency from ASM
//		I think we should consider this in the future.
//		https://wiki.osdev.org/Detecting_CPU_Speed

/**
 * @brief Initializes the kernel timer
 * 
 * @param frequency Frequency to set the clock
 */
void initTimer(uint32_t frequency);

#endif /* TIMER_H */