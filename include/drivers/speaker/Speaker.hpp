/**
 * @file Speaker.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_SPEAKER_HPP
#define PANIX_SPEAKER_HPP

#include <common/types.hpp>
#include <cpu/port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <drivers/Driver.hpp>
#include <lib/kprint.hpp>

#define SPEAKER_COMMAND_PORT 0x43
#define SPEAKER_DATA_PORT_2 0x42
#define SPEAKER_DATA_PORT_1 0x61

class Speaker : public Driver {
    private:
        uint32_t div;
        uint8_t tmp;
        
    public:
        Speaker();
        ~Speaker();
        virtual void activate();
        void playSound(uint32_t freqeuncy);
        void stopSound();
        void beep(uint32_t freq, uint32_t dur);
        /**
         * @brief Returns the short tag type of the driver. Used to identify
         * the driver and its purpose. Used by the driver manager to get a
         * specific driver type.
         * 
         * @return char* Short driver type tag
         */
        char* getDriverTypeTag();
};

#endif /* PANIX_SPEAKER_HPP */