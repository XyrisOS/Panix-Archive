/**
 * @file RTC.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_RTC_DRIVER
#define PANIX_RTC_DRIVER

#include <types.hpp>
#include <cpu/port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <drivers/Driver.hpp>
#include <drivers/DriverManager.hpp>
#include <libc/string.hpp>
#include <libc/kprint.hpp>

#define CMOS_PORT 0x70
#define DATA_PORT 0x71

#define CURRENT_YEAR 2019
#define CENTURY_REGISTER 0x00

class RTC : public InterruptHandler, public Driver {
    private:
        uint8_t second;
        uint8_t minute;
        uint8_t hour;
        uint8_t day;
        uint8_t month;
        uint32_t year;
        char* getDayNameFromInt(int day);
        int getUpdateInProgress();
        unsigned char getRTCRegister(int reg);
        void readRTC();
        
    public:
        RTC(InterruptManager* interruptManager);
        ~RTC();
        void activate();
        void deactivate();
        void printTimeAndDate();
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

#endif /* PANIX_RTC_DRIVER */