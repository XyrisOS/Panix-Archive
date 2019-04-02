#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <types.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <cpu/Port/Port.hpp>

class KeyboardDriver : public InterruptHandler
{
    private:
        Port8Bit dataPort;
        Port8Bit commandPort;
    public:
        KeyboardDriver(InterruptManager* manager);
        ~KeyboardDriver();
        virtual uint32_t handleInterrupt(uint32_t esp);
};

#endif /* KEYBOARD_HPP */