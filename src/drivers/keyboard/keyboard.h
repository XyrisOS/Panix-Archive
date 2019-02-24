#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../../cpu/isr.h"
#include "../../cpu/type.h"
#include "../../kernel/kernel.h"
#include "../../libc/function.h"
#include "../../libc/string.h"
#include "../driver.h"
#include "../screen/screen.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define UP_ARROW 0x48
#define SCANCODE_MAX 57

class Keyboard : public Driver {
    public:
        /**
         * @brief An array of human readable names for each scancode
         * 
         */
        static const char* scancodeName[];

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
        static void initialize();
    
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
};

#endif /* KEYBOARD_H */