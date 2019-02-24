/**
 * File: ports.h
 * Author: Keeton Feavel and James Osborne
 */

#ifndef PORTS_H
#define PORTS_H

#include "../type.h"

/**
 * @brief Get the Port Byte object
 * 
 * @param port 
 * @return uint8_t 
 */
uint8_t getPortByte(uint16_t port);

/**
 * @brief Set the Port Byte object
 * 
 * @param port 
 * @param data 
 */
void setPortByte(uint16_t port, uint8_t data);

/**
 * @brief Get the Port Word object
 * 
 * @param port 
 * @return uint16_t 
 */
uint16_t getPortWord(uint16_t port);

/**
 * @brief Set the Port Word object
 * 
 * @param port 
 * @param data 
 */
void setPortWord(uint16_t port, uint16_t data);

#endif /* PORTS_H */