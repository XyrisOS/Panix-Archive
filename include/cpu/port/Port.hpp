/**
 * @file Port.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief Ports header file. Provides inline functions
 * for getting and setting values at different ports.
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_PORT_HPP
#define PANIX_PORT_HPP

#include <types.hpp>

// Byte (8 bits)
uint8_t readByte(uint16_t _port);
void writeByte(uint16_t _port, uint8_t _data);
void writeByteSlow(uint16_t _port, uint8_t _data);

// Word (16 bits)
uint16_t readWord(uint16_t _port);
void writeWord(uint16_t _port, uint16_t _data);

// Long (32 bits)
uint32_t readLong(uint16_t _port);
void writeLong(uint16_t _port, uint32_t _data);

// Long long (64 bits)
// Lol not yet

#endif /* PANIX_PORT_HPP */