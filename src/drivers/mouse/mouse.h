/**
 * @file mouse.h
 * @author Keeton Feavel and James Osborne
 * @brief Mouse driver header file. Provides a class
 * for all mouse related functionality at a kernel level.
 * @version 0.1
 * @date 2019-03-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MOUSE_H
#define MOUSE_H

// TODO: There might be more includes than necessary.
//       Copied over from Keyboard due to similarities.
#include "../../cpu/isr/isr.h"
#include "../../cpu/type.h"
#include "../../kernel/kernel.h"
#include "../../libc/function/function.h"
#include "../../libc/string/string.h"
#include "../driver.h"
#include "../screen/screen.h"

#define PACKETS_IN_PIPE 1024
#define DISCARD_POINT 32

#define MOUSE_IRQ 12

#define MOUSE_PORT   0x60
#define MOUSE_STATUS 0x64
#define MOUSE_ABIT   0x02
#define MOUSE_BBIT   0x01
#define MOUSE_WRITE  0xD4
#define MOUSE_F_BIT  0x20
#define MOUSE_V_BIT  0x08

namespace drivers {
    class Mouse : public Driver {
        public:
            /**
             * @brief 
             * 
             * @param a_type 
             */
            void mouse_wait(uint8_t a_type);
            
            /**
             * @brief 
             * 
             * @param write 
             */
            void mouse_write(uint8_t write);

            /**
             * @brief 
             * 
             * @return uint8_t 
             */
            uint8_t mouse_read();

            /**
             * @brief 
             * 
             * @param regs 
             */
            void callback(registers_t regs);

            /**
             * @brief 
             * 
             */
            void initialize();
        private:
            //
    };
}

#endif /* MOUSE_H */