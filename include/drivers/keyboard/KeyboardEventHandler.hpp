#ifndef KEYBOARD_EVENT_HANDLER_HPP
#define KEYBOARD_EVENT_HANDLER_HPP

#include <libc/ctype.hpp>
#include <libc/kprint.hpp>
#include <libc/tty.hpp>

class KeyboardEventHandler {
    private:
        /**
         * @brief Variable to determine if the user is holding the shift key
         * 
         */
        bool isShiftEnabled;
    public:
        /**
         * @brief Construct a new Keyboard Event Handler object
         * 
         */
        KeyboardEventHandler();
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
         * @brief Prints a backspace.
         * 
         */
        virtual void backspace();
};

#endif /* KEYBOARD_EVENT_HANDLER_HPP */