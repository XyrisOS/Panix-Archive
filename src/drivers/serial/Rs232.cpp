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
#include <libc/kprint.hpp>

Rs232::Rs232(uint32_t portNum, InterruptManager* interruptManager) :
    InterruptHandler(interruptManager, portNum == COM1 ? COM1_IRQ : COM2_IRQ),
    dataReg(portNum + DATA_REG),
    interruptEnableReg(portNum + INTERRUPT_ENABLE_REG),
    iIdReg(portNum + INTERRUPT_IDENTIFICATION_REG),
    lineControlReg(portNum + LINE_CONTROL_REG),
    modemControlReg(portNum + MODEM_CONTROL_REG),
    lineStatusReg(portNum + LINE_STATUS_REG),
    modemStatusReg(portNum + MODEM_STATUS_REG),
    scratchReg(portNum + SCRATCH_REG) {

}

// stubbed for now
Rs232::~Rs232() {}

char Rs232::readSerial() {
    while (serialReceived() == 0);
    return dataReg.read();
}

int Rs232::serialReceived() {
    return lineStatusReg.read() & 1;
}

int Rs232::isTransmitEmpty() {
    return lineStatusReg.read() & 0x20;
}

void Rs232::writeSerial(char a) {
    while (isTransmitEmpty() == 0);
    dataReg.write(a);
}

void Rs232::activate() {
    interruptEnableReg.write(0x00);
    lineControlReg.write(0x80);
    dataReg.write(0x03);
    interruptEnableReg.write(0x00);
    lineControlReg.write(0x03);
    iIdReg.write(0xC7);
    modemControlReg.write(0x0B);
    lineControlReg.write(0x00);
    interruptEnableReg.write(0x01);
}

void Rs232::deactivate() {

}

void Rs232::print(char* str) {
    int i = 0;
    while (str[i] != 0)
    {
        writeSerial(str[i]);
        ++i;
    }
}

uint32_t Rs232::handleInterrupt(uint32_t esp) {
    print("INT\n");
    return esp;
}

char* Rs232::getDriverTypeTag() {
    return "RS232";
}
