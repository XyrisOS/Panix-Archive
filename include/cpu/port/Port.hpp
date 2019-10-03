/**
 * @file Port.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief Ports header file. Provides inline functions
 * for getting and setting values at different ports.
 * An I/O port is usually used as a technical term for 
 * a specific address on the x86's IO bus. This bus 
 * provides communication with devices in a fixed 
 * order and size, and was used as an alternative 
 * to memory access. (https://wiki.osdev.org/I/O_Ports)
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_PORT_HPP
#define PANIX_PORT_HPP

#include <types.hpp>

/**
 * @brief Reads a byte (8 bits) off the CPU bus at a given port address
 * 
 * @param port Port address
 * @return uint8_t Returned data byte
 */
inline uint8_t readByte(uint16_t port) {
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}
/**
 * @brief Writes a byte (8 bits) to the CPU bus at a given port address
 * 
 * @param port Port address
 * @param data Byte to be written to the port
 */
inline void writeByte(uint16_t port, uint8_t data) {
    __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (port));
}
/**
 * @brief Writes a byte (8 bits) slowly to the CPU bus at a given port address
 * 
 * @param port Port address
 * @param data Byte to be written to the port
 */
inline void writeByteSlow(uint16_t port, uint8_t data) {
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (port));
}
/**
 * @brief Reads a word (16 bits) off the CPU bus at a given port address
 * 
 * @param port Port address
 * @return uint8_t Returned data word
 */
inline uint16_t readWord(uint16_t port) {
    uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}
/**
 * @brief Writes a word (16 bits) to the CPU bus at a given port address
 * 
 * @param port Port address
 * @param data Word to be written to the port
 */
inline void writeWord(uint16_t port, uint16_t data) {
    __asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (port));
}
/**
 * @brief Reads a long (32 bits) off the CPU bus at a given port address
 * 
 * @param port Port address
 * @return uint8_t Returned data long
 */
inline uint32_t readLong(uint16_t port) {
    uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}
/**
 * @brief Writes a long (32 bits) to the CPU bus at a given port address
 * 
 * @param port Port address
 * @param data Long to be written to the port
 */
inline void writeLong(uint16_t port, uint32_t data) {
    __asm__ volatile("outl %0, %1" : : "a"(data), "Nd" (port));
}

#endif /* PANIX_PORT_HPP */