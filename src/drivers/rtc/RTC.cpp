#include <drivers/rtc/RTC.hpp>

RTC::RTC() : 
cmosPort(0x70), 
dataPort(0x71)
{
    // Initializer
    cmosPort.write(0x8A);
    dataPort.write(0x20);
}

RTC::~RTC() {
    //kprint("Destroying RTC\n");
}

void RTC::activate() {
    kprint("Activating RTC\n");
}

void RTC::deactivate() {
    kprint("Deactivating RTC\n");
}
 
int RTC::getUpdateInProgress() {
    cmosPort.write(0x0A);
    return (dataPort.read() & 0x80);
}
 
uint8_t RTC::getRTCRegister(int reg) {
    cmosPort.write(reg);
    return dataPort.read();
}

char* RTC::getDayNameFromInt(int day) {
    switch (day) {
        case 1:
            return "Sunday";
        case 2:
            return "Monday";
        case 3:
            return "Tuesday";
        case 4:
            return "Wednesday";
        case 5:
            return "Thursday";
        case 6:
            return "Friday";
        case 7:
            return "Saturday";
        default:
            return "Noneday";
    };
}

void RTC::printTimeAndDate() {
    readRTC();
    char hourStr[3];
    char minuteStr[3];
    char dayStr[3];
    char monthStr[3];
    //kprint(getDayNameFromInt(weekday));
    intToString(hour, hourStr);
    intToString(minute, minuteStr);
    intToString(day, dayStr);
    intToString(month, monthStr);
    kprint("\nToday's Date: ");
    kprint(dayStr);
    kprint("/");
    kprint(monthStr);
    kprint(" - UTC: ");
    kprint(hourStr);
    kprint(":");
    kprint(minuteStr);
    kprint("\n\n");
}

/*
    Big thanks to the OSDev Wiki for providing this function. It saved me a lot of time an energy trying to
    debug and convert and do whatever to get RTC to work. I don't know who it was who wrote this code originally,
    but thanks a lot. Time in programming is the worst.
    Note: This uses the "read registers until you get the same values twice in a row" technique
    to avoid getting dodgy/inconsistent values due to RTC updates
    Note: An unsigned char is just a uint8_t. Who knew?
*/
void RTC::readRTC() {
    uint8_t century;
    uint8_t last_second;
    uint8_t last_minute;
    uint8_t last_hour;
    uint8_t last_day;
    uint8_t last_month;
    uint8_t last_year;
    uint8_t last_century;
    uint8_t registerB;

    while (getUpdateInProgress());  // Make sure an update isn't in progress
    second = getRTCRegister(0x00);
    minute = getRTCRegister(0x02);
    hour = getRTCRegister(0x04);
    day = getRTCRegister(0x07);
    month = getRTCRegister(0x08);
    year = getRTCRegister(0x09);
    if(CENTURY_REGISTER != 0) {
        century = getRTCRegister(CENTURY_REGISTER);
    }
 
    while( (last_second != second) || (last_minute != minute) || (last_hour != hour) ||
            (last_day != day) || (last_month != month) || (last_year != year) ||
            (last_century != century) ) 
    {
            last_second = second;
            last_minute = minute;
            last_hour = hour;
            last_day = day;
            last_month = month;
            last_year = year;
            last_century = century;
 
            while (getUpdateInProgress());  // Make sure an update isn't in progress
            second = getRTCRegister(0x00);
            minute = getRTCRegister(0x02);
            hour = getRTCRegister(0x04);
            day = getRTCRegister(0x07);
            month = getRTCRegister(0x08);
            year = getRTCRegister(0x09);
            if(CENTURY_REGISTER != 0) {
                  century = getRTCRegister(CENTURY_REGISTER);
            }
      }
 
    registerB = getRTCRegister(0x0B);

    // Convert BCD to binary values if necessary
    if (!(registerB & 0x04)) {
        second = (second & 0x0F) + ((second / 16) * 10);
        minute = (minute & 0x0F) + ((minute / 16) * 10);
        hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
        day = (day & 0x0F) + ((day / 16) * 10);
        month = (month & 0x0F) + ((month / 16) * 10);
        year = (year & 0x0F) + ((year / 16) * 10);
        if(CENTURY_REGISTER != 0) {
                century = (century & 0x0F) + ((century / 16) * 10);
        }
    }

    // Convert 12 hour clock to 24 hour clock if necessary
    if (!(registerB & 0x02) && (hour & 0x80)) {
        hour = ((hour & 0x7F) + 12) % 24;
    }

    // Calculate the full (4-digit) year
    if(CENTURY_REGISTER != 0) {
        year += century * 100;
    } else {
        year += (CURRENT_YEAR / 100) * 100;
        if(year < CURRENT_YEAR) year += 100;
    }
}