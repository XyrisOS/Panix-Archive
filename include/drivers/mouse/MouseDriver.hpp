/**
 * @file MouseDriver.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_MOUSE_DRIVER_HPP
#define PANIX_MOUSE_DRIVER_HPP

#include <types.hpp>
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
         * @param interruptManager 
         * @param mouseEventHandler 
         */
        MouseDriver(InterruptManager* interruptManager, MouseEventHandler* mouseEventHandler);
        /**
         * @brief Destroy the Mouse Driver object
         * 
         */
        ~MouseDriver();
        /**
         * @brief 
         * 
         * @param esp 
         * @return uint32_t 
         */
        virtual uint32_t handleInterrupt(uint32_t esp);
        /**
         * @brief Activates the mouse driver
         * 
         */
        virtual void activate();

        /**
         * @brief Used to update the mouse driver event handler
         * 
         * @param handler 
         */
        virtual void setHandler(MouseEventHandler* handler);
};

#endif /* PANIX_MOUSE_DRIVER_HPP */