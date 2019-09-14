#ifndef PANIX_RTC_DRIVER
#define PANIX_RTC_DRIVER

#include <types.hpp>
#include <cpu/port/Port.hpp>
#include <drivers/Driver.hpp>
#include <drivers/DriverManager.hpp>
#include <libc/string.hpp>
#include <libc/kprint.hpp>

#define CURRENT_YEAR 2019
#define CENTURY_REGISTER 0x00

class RTC : public Driver {
    private:
        Port8Bit cmosPort;
        Port8Bit dataPort;
        uint8_t second;
        uint8_t minute;
        uint8_t hour;
        uint8_t day;
        uint8_t month;
        uint8_t year;
        int getUpdateInProgress();
        unsigned char getRTCRegister(int reg);
        void readRTC();
    public:
        RTC();
        void activate();
        void deactivate();
        void printTimeAndDate();
};

#endif /* PANIX_RTC_DRIVER */