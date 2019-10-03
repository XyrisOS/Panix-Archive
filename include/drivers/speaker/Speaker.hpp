/**
 * @file Speaker.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief The PC Speaker is the most primitive sound 
 * device available on PC compatible systems. It is 
 * characterized by the distinctive "beeps" and "squeaks" 
 * that it can be made to produce and is therefore 
 * sometimes referred to as the "PC Beeper" or the 
 * "PC Squeaker". Not to be confused with an actual audio
 * device, this is the internal BIOS beeper.
 * (https://wiki.osdev.org/PC_Speaker)
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_SPEAKER_HPP
#define PANIX_SPEAKER_HPP

#include <types.hpp>
#include <cpu/port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <drivers/Driver.hpp>
#include <libc/kprint.hpp>

#define SPEAKER_COMMAND_PORT 0x43
#define SPEAKER_DATA_PORT_2 0x42
#define SPEAKER_DATA_PORT_1 0x61

class Speaker : public Driver {
    public:
        /**
         * @brief Construct a new Speaker driver object
         * 
         */
        Speaker();
        /**
         * @brief Destroy the Speaker object
         * 
         */
        ~Speaker();
        /**
         * @brief Activates the PC Speaker driver
         * 
         */
        void activate();
        /**
         * @brief Plays a sound on the PC Speaker at the given frequency indefinitely
         * 
         * @param freqeuncy Frequency of note
         */
        void playSound(uint32_t freqeuncy);
        /**
         * @brief Stops any noise being emitted by the PC Speaker
         * 
         */
        void stopSound();
        /**
         * @brief Plays a sound on the PC speaker at the given frequency for a given duraction
         * 
         * @param freq Frequency of note
         * @param dur Note duration
         */
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