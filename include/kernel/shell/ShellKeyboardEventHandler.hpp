/**
 * @file ShellKeyboardEventHandler.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_KEYBOARD_SHELL_EVENT_HANDLER
#define PANIX_KEYBOARD_SHELL_EVENT_HANDLER

#include <common/types.hpp>
#include <lib/string.hpp>
#include <drivers/keyboard/KeyboardEventHandler.hpp>
#include <kernel/shell/shell.hpp>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define UP_ARROW 0x48

class ShellKeyboardEventHandler : public KeyboardEventHandler {
    private:
        bool isShiftEnabled;
        Shell* console;
        char keyBuffer[256] = "\0";
        char lastCommand[256] = "\0";
        uint16_t lengthOfCurrentCommand = 0;
        void handleNewLine();
        void handleSpecialCharacters(char c);
        
    public:
        /**
         * @brief Construct a new Shell Keyboard Event Handler object
         * 
         */
        ShellKeyboardEventHandler();
        /**
         * @brief Callback for keyboard driver handler activation
         * 
         */
        void onActivate();
        /**
         * @brief Handles a non-ascii keyboard input
         * 
         * @param scancode 
         */
        void handleScancode(uint8_t scancode);
        /**
         * @brief Tell the driver if the shift key is being held
         * 
         * @param isShiftPressed 
         */
        void setShiftKey(bool isShiftPressed);
        /**
         * @brief Callback for when a key is pressed.
         * 
         * @param c 
         */
        void onKeyDown(char c);
        /**
         * @brief Callback for when a key is released.
         * 
         * @param c 
         */
        void onKeyUp(char c);
        /**
         * @brief Handles the backspace key
         * 
         */
        void backspace();
        /**
         * @brief Set the Console object
         * 
         * @param console 
         */
        void setConsole(Shell* console);
};

#endif /* PANIX_KEYBOARD_SHELL_EVENT_HANDLER */