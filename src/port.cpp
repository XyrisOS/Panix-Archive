//  Port manager for the EDIX kernel.
//  port.cpp
//  EDIX
//
//  Created by Keeton Feavel on 5/25/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#include "port.h"
#include "kprint.h"

#pragma mark Port functions

Port::Port(uint16_t port) {
    // Store the port number in the class variable
    this->portnumber = port;
    kprint_status(true, "PortService");
}

Port::~Port() {

}

#pragma mark - Port_8 functions

Port_8::Port_8(uint16_t port) : Port(port) {

}

Port_8::~Port_8() {

}

uint8_t Port_8::read() {
    uint8_t result;
    // Call assembly inb ("in byte") command
    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (this->portnumber));

    return result;
}

void Port_8::write(uint8_t msg) {
    // Call assembly outb ("out byte") command
    __asm__ volatile("outb %0, %1" : : "a" (msg), "Nd" (this->portnumber));
}

#pragma mark - Port_8_Slow functions

Port_8_Slow::Port_8_Slow(uint16_t port) : Port_8(port) {

}

Port_8_Slow::~Port_8_Slow() {

}

void Port_8_Slow::write(uint8_t msg) {
    // Call assembly outb ("out byte") command with commands to slow the process
    // TODO: Compiler throws warning about using register %eax instead of %ex. Look into this.
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (msg), "Nd" (this->portnumber));
}

#pragma mark - Port_16 functions

Port_16::Port_16(uint16_t port) : Port(port) {

}

Port_16::~Port_16() {

}

uint16_t Port_16::read() {
    uint16_t result;
    // Call assembly inw ("in word") command
    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (this->portnumber));

    return result;
}

void Port_16::write(uint16_t msg) {
    // Call assembly outw ("out word") command
    __asm__ volatile("outw %0, %1" : : "a" (msg), "Nd" (this->portnumber));
}

#pragma mark - Port_32 functions

Port_32::Port_32(uint16_t port) : Port(port) {

}

Port_32::~Port_32() {

}

uint32_t Port_32::read() {
    uint16_t result;
    // Call assembly inl ("in long") command
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (this->portnumber));

    return result;
}

void Port_32::write(uint32_t msg) {
    // Call assembly outl ("out long") command
    __asm__ volatile("outl %0, %1" : : "a" (msg), "Nd" (this->portnumber));
}