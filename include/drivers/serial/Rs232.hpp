/**
 * @file Rs232.hpp
 * @author Micah Switzer (mswitzer@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_RS232_DRIVER
#define PANIX_RS232_DRIVER

#include <types.hpp>
#include <cpu/port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <drivers/Driver.hpp>
#include <drivers/DriverManager.hpp>
#include <libc/string.hpp>
#include <libc/kprint.hpp>

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

#define COM1_IRQ 0x04
#define COM3_IRQ 0x04
#define COM2_IRQ 0x03
#define COM4_IRQ 0x03

#define DATA_REG 0
#define INTERRUPT_ENABLE_REG 1
#define INTERRUPT_IDENTIFICATION_REG 2
#define LINE_CONTROL_REG 3
#define MODEM_CONTROL_REG 4
#define LINE_STATUS_REG 5
#define MODEM_STATUS_REG 6
#define SCRATCH_REG 7

class Rs232 : public InterruptHandler, public Driver {
    private:
        char* lineBuffer[75];
        uint8_t lineIndex;
        uint16_t portBase;

        char readSerial();
        int serialReceived();
        int isTransmitEmpty();
        void writeSerial(char a);
    public:
        Rs232(uint16_t portNum, InterruptManager* interruptManager);
        ~Rs232();
        void activate();
        void deactivate();
        void print(char* str);
        /**
         * @brief 
         * 
         * @param esp 
         * @return uint32_t 
         */
        uint32_t handleInterrupt(uint32_t esp);
        /**
         * @brief Returns the short tag type of the driver. Used to identify
         * the driver and its purpose. Used by the driver manager to get a
         * specific driver type.
         * 
         * @return char* Short driver type tag
         */
        char* getDriverTypeTag();
};

#endif /* PANIX_RS232_DRIVER */