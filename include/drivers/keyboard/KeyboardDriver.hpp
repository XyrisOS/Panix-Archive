#ifndef KEYBOARD_DRIVER_HPP
#define KEYBOARD_DRIVER_HPP

#include <types.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <cpu/Port/Port.hpp>
#include <drivers/keyboard/KeyboardEventHandler.hpp>
#include <drivers/Driver.hpp>
#include <libc/printf.hpp>

class KeyboardEventHandler;

class KeyboardDriver : public InterruptHandler, public Driver {
    private:
        Port8Bit dataPort;
        Port8Bit commandPort;
        KeyboardEventHandler* keyboardEventHandler;
    public:
        /**
         * @brief Construct a new Keyboard Driver object
         * 
         * @param interruptManager 
         * @param keyboardEventHandler 
         */
        KeyboardDriver(InterruptManager* interruptManager, KeyboardEventHandler* keyboardEventHandler);
        /**
         * @brief Destroy the Keyboard Driver object
         * 
         */
        ~KeyboardDriver();
        /**
         * @brief 
         * 
         * @param esp 
         * @return uint32_t 
         */
        virtual uint32_t handleInterrupt(uint32_t esp);
        /**
         * @brief 
         * 
         */
        virtual void activate();
};

#endif /* KEYBOARD_DRIVER_HPP */