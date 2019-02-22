/**
 * File: ports.h
 * Author: Keeton Feavel
 */

#ifndef PORTS_H
#define PORTS_H

#include "../cpu/type.h"

/**
 * Read a byte from the specified port
 */
uint8_t getPortByte(uint16_t port);

/**
 * 
 */
void setPortByte(uint16_t port, uint8_t data);

/**
 * 
 */
uint16_t getPortWord(uint16_t port);

/**
 * 
 */
void setPortWord(uint16_t port, uint16_t data);

#endif /* PORTS_H */