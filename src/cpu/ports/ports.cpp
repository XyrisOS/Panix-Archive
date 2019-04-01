/**
 * @file ports.cpp
 * @author Keeton Feavel and James Osborne
 * @brief Ports definitions file
 * @version 0.1
 * @date 2019-02-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <cpu/ports/ports.hpp>

using namespace cpu;

/* Learned inline assembly in Linux Systems Progamming, but keeping it here as a reminder
 * '"=a" (result)'; set '=' the C variable '(result)' to the value of register e'a'x
 * '"d" (port)': map the C variable '(port)' into e'd'x register
 * Inputs and outputs are separated by colons.
*/

/*******************
* Public Functions *
********************/

uint8_t Ports::getPortByte(uint16_t port) {
    uint8_t result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

uint16_t Ports::getPortWord(uint16_t port) {
    uint16_t result;
    asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void Ports::setPortByte(uint16_t port, uint8_t data) {
    asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

void Ports::setPortWord(uint16_t port, uint16_t data) {
    asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}
