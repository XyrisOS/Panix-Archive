/**
 * @file KeyboardDriver.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_KEYBOARD_DRIVER_HPP
#define PANIX_KEYBOARD_DRIVER_HPP

#include <types.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <cpu/port/Port.hpp>
#include <drivers/keyboard/KeyboardEventHandler.hpp>
#include <drivers/Driver.hpp>
#include <libc/kprint.hpp>
#include <libc/string.hpp>
#include <kernel/shell/shell.hpp>

class KeyboardEventHandler;

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define UP_ARROW 0x48
#define SCANCODE_MAX 57

class KeyboardDriver : public InterruptHandler, public Driver {
    private:
        PortByte dataPort;
        PortByte commandPort;
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

        /**
         * @brief Used to update the keyboard event handler
         * 
         * @param handler 
         */
        virtual void setHandler(KeyboardEventHandler *handler);
};

#endif /* PANIX_KEYBOARD_DRIVER_HPP */