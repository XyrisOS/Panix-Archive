/**
 * @file Speaker.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
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
};

#endif /* PANIX_SPEAKER_HPP */