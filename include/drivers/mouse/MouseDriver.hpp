/**
 * @file MouseDriver.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief A (hopefully) simple PS/2 Mouse driver. 
 * Current PCs generally use PS2 mice, or a similar format 
 * that emulates a PS2 mouse. Serial mice are a much older 
 * technology that is no longer common.
 * (https://wiki.osdev.org/Mouse)
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_MOUSE_DRIVER_HPP
#define PANIX_MOUSE_DRIVER_HPP

#include <common/types.hpp>
#include <cpu/port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <drivers/mouse/MouseEventHandler.hpp>
#include <drivers/Driver.hpp>

#define MOUSE_COMMAND_PORT 0x60
#define MOUSE_DATA_PORT 0x64

class MouseEventHandler;

class MouseDriver : public InterruptHandler, public Driver {
    private:
        uint8_t buffer[3];
        uint8_t offset;
        uint8_t buttons;
        MouseEventHandler* mouseEventHandler;

    public:
        /**
         * @brief Construct a new Mouse Driver object
         * 
         * @param interruptManager Current active interrupt manager
         * @param mouseEventHandler Mouse event handler designated to handle input
         */
        MouseDriver(InterruptManager* interruptManager, MouseEventHandler* mouseEventHandler);
        /**
         * @brief Destroy the Mouse Driver object
         * 
         */
        ~MouseDriver();
        /**
         * @brief Handles an associated interrupt assigned in the constructor
         * 
         * @param esp Stack pointer
         * @return uint32_t Returned stack pointer
         */
        uint32_t handleInterrupt(uint32_t esp);
        /**
         * @brief Activates the mouse driver
         * 
         */
        void activate();
        /**
         * @brief Used to update the mouse driver event handler
         * 
         * @param handler New mouse handler designated to recieve input
         */
        void setHandler(MouseEventHandler* handler);
        /**
         * @brief Returns the short tag type of the driver. Used to identify
         * the driver and its purpose. Used by the driver manager to get a
         * specific driver type.
         * 
         * @return char* Short driver type tag
         */
        char* getDriverTypeTag();
};

#endif /* PANIX_MOUSE_DRIVER_HPP */