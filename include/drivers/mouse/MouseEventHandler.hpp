/**
 * @file MouseEventHandler.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief An interface for all classes which wish to
 * recieve mouse input. To recieve input, the appropriate
 * class must import this and inherit it publicly and then
 * implement all of the virtual functions below.
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_MOUSE_EVENT_HANDLER_HPP
#define PANIX_MOUSE_EVENT_HANDLER_HPP

#include <common/types.hpp>
#include <lib/kprint.hpp>

class MouseEventHandler {
    public:
        /**
         * @brief Construct a new Mouse Event Handler object
         * 
         */
        MouseEventHandler();
        /**
         * @brief Handler activation callback function
         * 
         */
        virtual void onActivate();
        /**
         * @brief Handles a mouse button down event
         * 
         * @param button 
         */
        virtual void onMouseDown(uint8_t button);
        /**
         * @brief Handles a mouse button up event
         * 
         * @param button 
         */
        virtual void onMouseUp(uint8_t button);
        /**
         * @brief Handles a mouse move to an x and y coordinate
         * 
         * @param x Horizontal coordinate
         * @param y Vertical coordinate
         */
        virtual void onMouseMove(int x, int y);
};

#endif /* PANIX_MOUSE_EVENT_HANDLER_HPP */