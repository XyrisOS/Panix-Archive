/**
 * File: timer.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef TIMER_H
#define TIMER_H

#include "../drivers/screen/screen.h"
#include "../libc/string.h"
#include "isr.h"
#include "ports.h"
#include "type.h"

/**
 * @brief 
 * 
 * @param frequency 
 */
void initTimer(uint32_t frequency);

#endif /* TIMER_H */