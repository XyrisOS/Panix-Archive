/**
 * @file MouseEventHandler.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
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
         * @brief 
         * 
         */
        virtual void onActivate();
        /**
         * @brief 
         * 
         * @param button 
         */
        virtual void onMouseDown(uint8_t button);
        /**
         * @brief 
         * 
         * @param button 
         */
        virtual void onMouseUp(uint8_t button);
        /**
         * @brief 
         * 
         * @param x 
         * @param y 
         */
        virtual void onMouseMove(int x, int y);
};

#endif /* PANIX_MOUSE_EVENT_HANDLER_HPP */