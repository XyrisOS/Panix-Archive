/**
 * @file KeyboardDriver.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief A (hopefully) simple PS/2 Keyboard driver. 
 * The PS/2 Keyboard accepts commands and sends responses to 
 * those commands, and also sends scan codes indicating when 
 * a key was pressed or released. Keep in mind that these 
 * scan codes (from the tables below) may be altered 
 * (i.e. translated) by the PS/2 controller, depending on 
 * the controller's settings. (https://wiki.osdev.org/Keyboard)
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

#define KEYBOARD_COMMAND_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define UP_ARROW 0x48
#define SCANCODE_MAX 57

class KeyboardDriver : public InterruptHandler, public Driver {
    private:
        KeyboardEventHandler* keyboardEventHandler; // Current keyboard event handler (Handles data recieved by driver)
        
    public:
        /**
         * @brief Construct a new Keyboard Driver object
         * 
         * @param interruptManager Current active interrupt manager
         * @param keyboardEventHandler Keyboard event handler designated to handle input
         */
        KeyboardDriver(InterruptManager* interruptManager, KeyboardEventHandler* keyboardEventHandler);
        /**
         * @brief Destroy the Keyboard Driver object
         * 
         */
        ~KeyboardDriver();
        /**
         * @brief Handles an associated interrupt assigned in the constructor
         * 
         * @param esp Stack pointer
         * @return uint32_t Returned stack pointer
         */
        uint32_t handleInterrupt(uint32_t esp);
        /**
         * @brief Activates the keyboard driver
         * 
         */
        void activate();
        /**
         * @brief Used to update the keyboard event handler
         * 
         * @param handler New keyboard handler designated to recieve input
         */
        void setHandler(KeyboardEventHandler *handler);
        /**
         * @brief Returns the short tag type of the driver. Used to identify
         * the driver and its purpose. Used by the driver manager to get a
         * specific driver type.
         * 
         * @return char* Short driver type tag
         */
        char* getDriverTypeTag();
};

#endif /* PANIX_KEYBOARD_DRIVER_HPP */