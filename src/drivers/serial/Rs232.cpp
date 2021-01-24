/**
 * @file Rs232.cpp
 * @author Micah Switzer (mswitzer@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <drivers/serial/Rs232.hpp>

Rs232::Rs232(uint16_t portNum, InterruptManager* interruptManager) :
    InterruptHandler(interruptManager, 0x20 + (portNum == COM1 ? COM1_IRQ : COM2_IRQ)),
    portBase(portNum),
    lineIndex(0) {
}

Rs232::~Rs232() {
// stubbed
}

char Rs232::readSerial() {
    while (serialReceived() == 0);
    return readByte(portBase + DATA_REG);
}

int Rs232::serialReceived() {
    return readByte(portBase + LINE_STATUS_REG) & 1;
}

int Rs232::isTransmitEmpty() {
    return readByte(portBase + LINE_STATUS_REG) & 0x20;
}

void Rs232::writeSerial(char a) {
    while (isTransmitEmpty() == 0);
    writeByte(portBase + DATA_REG, a);
}

void Rs232::activate() {
    // disable interrupts
    writeByte(portBase + INTERRUPT_ENABLE_REG, 0x00);
    writeByte(portBase + LINE_CONTROL_REG, 0x80);
    writeByte(portBase + DATA_REG, 0x03);
    writeByte(portBase + INTERRUPT_ENABLE_REG, 0x00);
    writeByte(portBase + LINE_CONTROL_REG, 0x03);
    writeByte(portBase + INTERRUPT_IDENTIFICATION_REG, 0xC7);
    writeByte(portBase + MODEM_CONTROL_REG, 0x0B);
    writeByte(portBase + LINE_CONTROL_REG, 0x00);
    // re-enable interrupts
    writeByte(portBase + INTERRUPT_ENABLE_REG, 0x01);
}

void Rs232::deactivate() {
// stubbed
}

void Rs232::print(char* str) {
    int i = 0;
    while (str[i] != 0) {
        writeSerial(str[i]);
        ++i;
    }
}

uint32_t Rs232::handleInterrupt(uint32_t esp) {
    //if (lineIndex == BUF_SIZE)
    char str[2] = { readSerial(), '\0' };
    if (str[0] == '\r') {
        print("\n");
    }
    print(str);
    return esp;
}

char* Rs232::getDriverTypeTag() {
    return "RS232";
}
