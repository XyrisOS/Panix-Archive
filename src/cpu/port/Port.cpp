
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
PortByte::PortByte(uint16_t portnumber) 
    : Port(portnumber) 
{
    // Stubbed
}

inline uint8_t PortByte::read8(uint16_t port) {
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}

inline void PortByte::write8(uint16_t port, uint8_t data) {
    __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (port));
}

void PortByte::write(uint8_t data) {
    write8(portnumber, data);
}

uint8_t PortByte::read() {
    return read8(portnumber);
}

/* Port 8-Bit Slow */
PortByteSlow::PortByteSlow(uint16_t portnumber)
    : PortByte(portnumber)
{
    // Stubbed
}

inline void PortByteSlow::write8Slow(uint16_t port, uint8_t data) {
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (port));
}

void PortByteSlow::write(uint8_t data) {
    write8Slow(portnumber, data);
}

/* Port 16-Bit */
PortWord::PortWord(uint16_t portnumber)
    : Port(portnumber)
{
    // Stubbed
}

inline uint16_t PortWord::read16(uint16_t port) {
    uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}

inline void PortWord::write16(uint16_t port, uint16_t data) {
    __asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (port));
}

void PortWord::write(uint16_t data) {
    write16(portnumber, data);
}

uint16_t PortWord::read() {
    return read16(portnumber);
}

/* Port 32-Bit */
PortLong::PortLong(uint16_t portnumber)
    : Port(portnumber)
{
    // Stubbed
}

inline uint32_t PortLong::read32(uint16_t port) {
    uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}

inline void PortLong::write32(uint16_t port, uint32_t data) {
    __asm__ volatile("outl %0, %1" : : "a"(data), "Nd" (port));
}

void PortLong::write(uint32_t data) {
    write32(portnumber, data);
}

uint32_t PortLong::read() {
    return read32(portnumber);
}