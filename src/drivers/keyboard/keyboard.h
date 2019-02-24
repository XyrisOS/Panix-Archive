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
         * @brief 
         * 
         */
        static const char* scancodeName[];

        /**
         * @brief 
         * 
         */
        static const char scancodeAscii[];

        /**
         * @brief 
         * 
         */
        static void callback(registers_t regs);
        /**
         * @brief 
         * 
         */
        static void initialize();
    
    private:
        /**
         * @brief 
         * 
         */
        inline static char keyBuffer[256];

        inline static char lastCommand[256];
};

#endif /* KEYBOARD_H */