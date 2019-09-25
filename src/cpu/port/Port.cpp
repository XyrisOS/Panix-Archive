
#include <cpu/port/Port.hpp>

/* Port */
Port::Port(uint16_t portnumber) {
    this->portnumber = portnumber;
}
/*
Port::~Port() {
    
}
*/
/* Port 8-Bit */
Port8Bit::Port8Bit(uint16_t portnumber) 
    : Port(portnumber) 
{
    // Stubbed
}
/*
Port8Bit::~Port8Bit() {
    
}
*/
inline uint8_t Port8Bit::read8(uint16_t _port) {
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
    return result;
}

inline void Port8Bit::write8(uint16_t _port, uint8_t _data) {
    __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
}

void Port8Bit::write(uint8_t data) {
    write8(portnumber, data);
}

uint8_t Port8Bit::read() {
    return read8(portnumber);
}

/* Port 8-Bit Slow */
Port8BitSlow::Port8BitSlow(uint16_t portnumber)
    : Port8Bit(portnumber)
{
    // Stubbed
}
/*
Port8BitSlow::~Port8BitSlow() {

}
*/

inline void Port8BitSlow::write8Slow(uint16_t _port, uint8_t _data) {
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
}

void Port8BitSlow::write(uint8_t data) {
    write8Slow(portnumber, data);
}

/* Port 16-Bit */
Port16Bit::Port16Bit(uint16_t portnumber)
    : Port(portnumber)
{
    // Stubbed
}
/*
Port16Bit::~Port16Bit() {

}
*/
inline uint16_t Port16Bit::read16(uint16_t _port) {
    uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
    return result;
}

inline void Port16Bit::write16(uint16_t _port, uint16_t _data) {
    __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
}

void Port16Bit::write(uint16_t data) {
    write16(portnumber, data);
}

uint16_t Port16Bit::read() {
    return read16(portnumber);
}

/* Port 32-Bit */
Port32Bit::Port32Bit(uint16_t portnumber)
    : Port(portnumber)
{
    // Stubbed
}
/*
Port32Bit::~Port32Bit() {

}
*/
inline uint32_t Port32Bit::read32(uint16_t _port) {
    uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
    return result;
}

inline void Port32Bit::write32(uint16_t _port, uint32_t _data) {
    __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
}

void Port32Bit::write(uint32_t data) {
    write32(portnumber, data);
}

uint32_t Port32Bit::read() {
    return read32(portnumber);
}