/**
 * @file mouse.cpp
 * @author Keeton Feavel and James Osborne
 * @brief Mouse driver definitions file
 * @version 0.1
 * @date 2019-03-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "mouse.h"

using namespace drivers;

/*******************
* Public Functions *
********************/
registers_t Mouse::callback(registers_t regs) {
    // NOTE: This is from WYOOS. The other link in the header works well with ours
    //       but is much more complicated, so it depends on how we want to attack this.
    uint8_t status = cpu::Ports::getPortByte(MOUSE_IRQ);
    if (!(status & 0x20)) {
        return regs;
    }

    buffer[offset] = cpu::Ports::getPortByte(MOUSE_IRQ);
    offset = (offset + 1) % 3;

    if (offset == 0) {
        if (buffer[1] != 0 || buffer[2] != 0) {
            onMouseMove((int8_t) buffer[1], -((int8_t) buffer[2]));
        }
        for (uint8_t i = 0; i < 3; i++) {
            if ((buffer[0] & (0x1 << i)) != (buttons & (0x1<<i))) {
                if(buttons & (0x1 << i)) {
                    onMouseUp(i + 1);
                } else {
                    onMouseDown(i + 1);
                }
            }
        }
        buttons = buffer[0];
    }
    return regs;
}

void Mouse::initialize() {
    // TODO: Is this the right IRQ for the mouse?
    // cpu::ISR::registerInterruptHandler(MOUSE_IRQ, Keyboard::callback);
    offset = 0;
    buttons = 0;
    
    // This is all WYOOS stuff, so like I stated previously, this could use some serious rewriting.
    cpu::Ports::setPortByte(MOUSE_IRQ, 0xA8);
    cpu::Ports::setPortByte(MOUSE_IRQ, 0x20); // command 0x60 = read controller command byte
    uint8_t status = cpu::Ports::getPortByte(MOUSE_IRQ) | 2;
    cpu::Ports::setPortByte(MOUSE_IRQ, 0x60); // command 0x60 = set controller command byte
    cpu::Ports::setPortByte(MOUSE_IRQ, status);

    cpu::Ports::setPortByte(MOUSE_IRQ, 0xD4);
    cpu::Ports::setPortByte(MOUSE_IRQ, 0xF4);
    cpu::Ports::getPortByte(MOUSE_IRQ);
}

/********************
* Private Functions *
*********************/
void Mouse::onActivate() {
    drivers::Screen::kprint("Mouse driver activated.");
    drivers::Screen::kprintNewLine();
}

void Mouse::onMouseDown(uint8_t button) {
    drivers::Screen::kprint("Mouse button down.");
    drivers::Screen::kprintNewLine();
}

void Mouse::onMouseUp(uint8_t button) {
    drivers::Screen::kprint("Mouse button up.");
    drivers::Screen::kprintNewLine();
}

void Mouse::onMouseMove(int x, int y) {
    drivers::Screen::kprint("Mouse moved.");
    drivers::Screen::kprintNewLine();
}