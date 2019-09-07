
#include <drivers/mouse/MouseDriver.hpp>

void kprint(const char* str);

MouseDriver::MouseDriver(InterruptManager* interruptManager, MouseEventHandler* mouseEventHandler)
    : InterruptHandler(interruptManager, 0x2C),
      dataPort(0x60),
      commandPort(0x64) {
    this->mouseEventHandler = mouseEventHandler;
}

MouseDriver::~MouseDriver() {}

void MouseDriver::activate() {
    uint16_t* videoMemory = (uint16_t*)0xb8000;
    offset = 0;
    buttons = 0;
    
    if (mouseEventHandler != nullptr) {
        kprint("Activating mouse event handler\n");
        mouseEventHandler->onActivate();
    }

    commandPort.write(0xA8);
    commandPort.write(0x20); // command 0x60 = read controller command byte
    uint8_t status = dataPort.read() | 2;
    commandPort.write(0x60); // command 0x60 = set controller command byte
    dataPort.write(status);

    commandPort.write(0xD4);
    dataPort.write(0xF4);
    dataPort.read();
}

uint32_t MouseDriver::handleInterrupt(uint32_t esp) {
    uint8_t status = commandPort.read();
    if (!(status & 0x20) || mouseEventHandler == nullptr) {
        return esp;
    }

    buffer[offset] = dataPort.read();
    offset = (offset + 1) % 3;

    if (offset == 0) { 
        if (buffer[1] != 0 || buffer[2] != 0 ) { 
            mouseEventHandler->onMouseMove(buffer[1], -buffer[2]);
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