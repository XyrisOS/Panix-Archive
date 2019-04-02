
#include <drivers/MouseDriver.hpp>

MouseDriver::MouseDriver(InterruptManager* interruptManager)
    : InterruptHandler(interruptManager, 0x2C),
      dataPort(0x60),
      commandPort(0x64)
{
    uint16_t* videoMemory = (uint16_t*)0xb8000;
    offset = 0;
    buttons = 0;
    x = 40;
    y = 12;
    videoMemory[80 * y + x] = (videoMemory[80 * y + x] & 0x0F00) << 4
                            | (videoMemory[80 * y + x] & 0xF000) >> 4
                            | (videoMemory[80 * y + x] & 0x00FF);

    commandPort.write(0xA8);
    commandPort.write(0x20); // command 0x60 = read controller command byte
    uint8_t status = dataPort.read() | 2;
    commandPort.write(0x60); // command 0x60 = set controller command byte
    dataPort.write(status);

    commandPort.write(0xD4);
    dataPort.write(0xF4);
    dataPort.read();
}

MouseDriver::~MouseDriver()
{
}

uint32_t MouseDriver::handleInterrupt(uint32_t esp)
{
    uint8_t status = commandPort.read();
    if (!(status & 0x20)) {
        return esp;
    }

    buffer[offset] = dataPort.read();
    offset = (offset + 1) % 3;

    if (offset == 0) { 
        if (buffer[1] != 0 || buffer[2] != 0 ) { 
            static uint16_t* videoMemory = (uint16_t*) 0xb8000;
            videoMemory[80 * y + x] = (videoMemory[80 * y + x] & 0x0F00) << 4
                                    | (videoMemory[80 * y + x] & 0xF000) >> 4
                                    | (videoMemory[80 * y + x] & 0x00FF);

            x += buffer[1];
            if (x >= 80) {
                x = 79;
            }
            if (x < 0) {
                x = 0;
            }
            y -= buffer[2];
            if (y >= 25) { 
                y = 24;
            }
            if (y < 0) { 
                y = 0;
            }

            videoMemory[80 * y + x] = (videoMemory[80 * y + x] & 0x0F00) << 4
                                    | (videoMemory[80 * y + x] & 0xF000) >> 4
                                    | (videoMemory[80 * y + x] & 0x00FF);
        }

        /*
        for(uint8_t i = 0; i < 3; i++)
        {
            if((buffer[0] & (0x1<<i)) != (buttons & (0x1<<i)))
            {
                if(buttons & (0x1<<i))
                    handler->OnMouseButtonReleased(i+1);
                else
                    handler->OnMouseButtonPressed(i+1);
            }
        }
        buttons = buffer[0];
        */
    }
    return esp;
}