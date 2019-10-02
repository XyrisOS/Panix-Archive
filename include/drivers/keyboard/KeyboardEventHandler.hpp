/**
 * @file KeyboardEventHandler.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_KEYBOARD_EVENT_HANDLER_HPP
#define PANIX_KEYBOARD_EVENT_HANDLER_HPP

#include <libc/ctype.hpp>
#include <libc/kprint.hpp>
#include <libc/tty.hpp>

class KeyboardEventHandler {
    public:
        /**
         * @brief Construct a new Keyboard Event Handler object
         * 
         */
        KeyboardEventHandler();
        /**
         * @brief Handler activation callback function
         * 
         */
        virtual void onActivate();
        /**
         * @brief Handles a non-ascii keyboard input
         * 
         * @param scancode 
         */
        virtual void handleScancode(uint8_t scancode);
        /**
         * @brief Set the Shift Key object
         * 
         * @param isShiftPressed 
         */
        virtual void setShiftKey(bool isShiftPressed);
        /**
         * @brief Keyboard key pressed handler
         * 
         * @param c Keyboard associated character to handle.
         */
        virtual void onKeyDown(char c);
        /**
         * @brief Keyboard key released handler
         * 
         * @param c Keyboard associated character to handle.
         */
        virtual void onKeyUp(char c);
        /**
         * @brief Handles backspace
         * 
         */
        virtual void backspace();
};

#endif /* PANIX_KEYBOARD_EVENT_HANDLER_HPP */