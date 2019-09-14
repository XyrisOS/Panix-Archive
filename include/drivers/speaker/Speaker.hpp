#ifndef PANIX_SPEAKER_HPP
#define PANIX_SPEAKER_HPP
#include <types.hpp>
#include <cpu/port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <drivers/Driver.hpp>
#include <libc/kprint.hpp>

class Speaker : public Driver {
    private:
        uint32_t div;
        uint8_t tmp;
        Port8Bit port43;
        Port8Bit port42;
        Port8Bit port61;
    public:
        Speaker();
        ~Speaker();
        virtual void activate();
        void playSound(uint32_t freqeuncy);
        void stopSound();
        void beep(uint32_t freq, uint32_t dur);
};

#endif /* PANIX_SPEAKER_HPP */