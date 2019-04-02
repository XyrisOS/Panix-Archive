#ifndef KEYBOARD_DRIVER_HPP
#define KEYBOARD_DRIVER_HPP

#include <types.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <cpu/Port/Port.hpp>
#include <drivers/keyboard/KeyboardEventHandler.hpp>
#include <drivers/Driver.hpp>

class KeyboardEventHandler;

class KeyboardDriver : public InterruptHandler, public Driver {
    private:
        Port8Bit dataPort;
        Port8Bit commandPort;
        KeyboardEventHandler* keyboardEventHandler;
    public:
        KeyboardDriver(InterruptManager* interruptManager, KeyboardEventHandler* keyboardEventHandler);
        ~KeyboardDriver();
        virtual uint32_t handleInterrupt(uint32_t esp);
        virtual void activate();
};

#endif /* KEYBOARD_DRIVER_HPP */