
#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <types.hpp>
#include <cpu/Port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <cpu/interrupts/InterruptManager.hpp>

class MouseDriver : public InterruptHandler
{
    private:
        Port8Bit dataPort;
        Port8Bit commandPort;
        uint8_t buffer[3];
        uint8_t offset;
        uint8_t buttons;

        int8_t x;
        int8_t y;
    public:
        MouseDriver(InterruptManager* interruptManager);
        ~MouseDriver();
        virtual uint32_t handleInterrupt(uint32_t esp);
};

#endif /* MOUSE_HPP */