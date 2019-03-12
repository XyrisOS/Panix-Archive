/**
 * @file mouse.h
 * @author Keeton Feavel and James Osborne
 * @brief Mouse driver header file. Provides a class
 * for all mouse related functionality at a kernel level.
 * 
 * References:
 * https://github.com/AlgorithMan-de/wyoos/blob/master/include/drivers/mouse.h
 * https://github.com/stevej/osdev/blob/master/kernel/devices/mouse.c
 * 
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
             * @param regs 
             */
            registers_t callback(registers_t regs);

            /**
             * @brief 
             * 
             */
            void initialize();
        private:
            /**
             * @brief 
             * 
             */
            void onActivate();

            /**
             * @brief 
             * 
             * @param button 
             */
            void onMouseDown(uint8_t button);

            /**
             * @brief 
             * 
             * @param button 
             */
            void onMouseUp(uint8_t button);

            /**
             * @brief 
             * 
             * @param x 
             * @param y 
             */
            void onMouseMove(int x, int y);

            uint8_t buffer[3];
            uint8_t offset;
            uint8_t buttons;
    };
}

#endif /* MOUSE_H */