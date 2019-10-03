/**
 * @file RTC.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief RTC is the Real Time Clock located in the CMOS.
 * The RTC, like the PIT, can be set to tick at a given
 * frequency and will listen for an IRQ of 0x08.
 * (https://wiki.osdev.org/RTC)
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
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

#define RTC_CMOS_PORT 0x70
#define RTC_DATA_PORT 0x71

#define CURRENT_YEAR 2019       // Needs to be updated every year!
#define CENTURY_REGISTER 0x00   // Needs to be updated every century!

class RTC : public InterruptHandler, public Driver {
    private:
        uint8_t second; // Current UTC second
        uint8_t minute; // Current UTC minute
        uint8_t hour;   // Current UTC hour
        uint8_t day;    // Current UTC day (not reliable)
        uint8_t month;  // Current UTC month
        uint32_t year;  // Current UTC year
        /**
         * @brief Get the Day Name From a day int value
         * 
         * @param day Day in integer value (1 = Sunday)
         * @return char* Day string name
         */
        char* getDayNameFromInt(int day);
        /**
         * @brief Returns an integer from the RTC device if a
         * RTC clock update is in progress
         * 
         * @return int Return code from RTC port
         */
        int getUpdateInProgress();
        /**
         * @brief Gets the resulting value from an RTC register (port)
         * 
         * @param reg Register (port) to be queried
         * @return unsigned char Resuling register (port) value
         */
        unsigned char getRTCRegister(int reg);
        /**
         * @brief Reads the RTC and fills in the time variables above.
         * 
         */
        void readRTC();
        
    public:
        /**
         * @brief Construct a new RTC driver object
         * 
         * @param interruptManager Current active kernel interrupt manager
         */
        RTC(InterruptManager* interruptManager);
        /**
         * @brief Destroy the RTC object
         * 
         */
        ~RTC();
        /**
         * @brief Activates the RTC driver
         * 
         */
        void activate();
        /**
         * @brief Deactivates the RTC driver
         * 
         */
        void deactivate();
        /**
         * @brief Prints the current time and date values loaded from the RTC
         * 
         */
        void printTimeAndDate();
        /**
         * @brief Handles an associated interrupt assigned in the constructor
         * 
         * @param esp Stack pointer
         * @return uint32_t Returned stack pointer
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