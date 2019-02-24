/**
 * @file keyboard.h
 * @author Keeton Feavel and James Osborne
 * @brief Keyboard driver header file. Provides a class
 * for translating scancodes to printable characters
 * and passing that on to the Screen driver.
 * @version 0.1
 * @date 2019-02-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../../cpu/isr/isr.h"
#include "../../cpu/type.h"
#include "../../kernel/kernel.h"
#include "../../libc/function/function.h"
#include "../../libc/string/string.h"
#include "../driver.h"
#include "../screen/screen.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define UP_ARROW 0x48
#define SCANCODE_MAX 57

namespace drivers {
    class Keyboard : public Driver {
        public:
            /**
             * @brief An array of human readable names for each scancode
             * 
             */
            static const char scancodeName[64][16];

            /**
             * @brief An array of ASCII symbols for each scancode
             * 
             */
            static const char scancodeAscii[];

            /**
             * @brief Called each time a keyboard interrupt is received
             * 
             * @param regs The struct representing all register. Currently unused.
             */
            static void callback(registers_t regs);

            /**
             * @brief Initializes the keyboard driver
             * 
             */
            void initialize();
        
        private:
            /**
             * @brief A buffer holding the text of a shell command
             * 
             */
            inline static char keyBuffer[256];

            /**
             * @brief A buffer holding the last shell command
             * 
             */
            inline static char lastCommand[256];

            /**
             * @brief Tracks the length of the current shell commands
             * 
             */
            inline static uint16_t lengthOfCurrentCommand;
    };
}

#endif /* KEYBOARD_H */