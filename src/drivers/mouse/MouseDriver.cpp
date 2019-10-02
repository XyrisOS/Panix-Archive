/**
 * @file MouseDriver.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#include <drivers/mouse/MouseDriver.hpp>

void kprint(const char* str);

MouseDriver::MouseDriver(InterruptManager* interruptManager, MouseEventHandler* mouseEventHandler)
    : InterruptHandler(interruptManager, 0x2C) {
    this->mouseEventHandler = mouseEventHandler;
}

MouseDriver::~MouseDriver() {}

void MouseDriver::activate() {
    kprint("Activating mouse driver\n");
    uint16_t* videoMemory = (uint16_t*)0xb8000;
    offset = 0;
    buttons = 0;
    
    if (mouseEventHandler != nullptr) {
        mouseEventHandler->onActivate();
    }

    writeByte(MOUSE_COMMAND_PORT, 0xA8);
    writeByte(MOUSE_COMMAND_PORT, 0x20); // command 0x60 = read controller command byte
    uint8_t status = readByte(MOUSE_DATA_PORT) | 2;
    writeByte(MOUSE_COMMAND_PORT, 0x60); // command 0x60 = set controller command byte
    writeByte(MOUSE_DATA_PORT, status);

    writeByte(MOUSE_COMMAND_PORT, 0xD4);
    writeByte(MOUSE_DATA_PORT, 0xF4);
    readByte(MOUSE_DATA_PORT);
}

uint32_t MouseDriver::handleInterrupt(uint32_t esp) {
    uint8_t status = readByte(MOUSE_COMMAND_PORT) ;
    if (!(status & 0x20) || mouseEventHandler == nullptr) {
        return esp;
    }

    buffer[offset] = readByte(MOUSE_DATA_PORT);
    offset = (offset + 1) % 3;

    if (offset == 0) { 
        if (buffer[1] != 0 || buffer[2] != 0 ) {
            mouseEventHandler->onMouseMove((int8_t)buffer[1], -((int8_t)buffer[2]));
        }

        for(uint8_t i = 0; i < 3; i++) {
            if ((buffer[0] & (0x1 << i)) != (buttons & (0x1 << i))) {
                if (buttons & (0x1 << i)) {
                    mouseEventHandler->onMouseUp(i + 1);
                } else {
                    mouseEventHandler->onMouseDown(i + 1);
                }
            }
        }
        buttons = buffer[0];
    }
    
    return esp;
}

void MouseDriver::setHandler(MouseEventHandler* handler) {
    this->mouseEventHandler = handler;
}
char* MouseDriver::getDriverTypeTag() {
    return "MOUSE";
}