
#include <types.hpp>
#include <cpu/GlobalDescriptorTable/GlobalDescriptorTable.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <drivers/keyboard/KeyboardDriver.hpp>
#include <drivers/mouse/MouseDriver.hpp>
#include <drivers/DriverManager.hpp>

void printf(const char* str) {
    static uint16_t* videoMemory = (uint16_t*) 0xb8000;

    static uint8_t x=0,y=0;
    
    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                videoMemory[80*y+x] = (videoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }
        
        if(x >= 80)
        {
            x = 0;
            y++;
        }
        
        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    videoMemory[80*y+x] = (videoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

class KeyboardPrintEventHandler : public KeyboardEventHandler {
    public:
        void onKeyDown(char c) {
            const char str[2] = {c, '\0'};
            printf(str);
        }
};

class ConsoleMouseEventHandler : public MouseEventHandler {
    private:
        int8_t x;
        int8_t y;

    public:
        ConsoleMouseEventHandler()
        {
        }
        
        virtual void onActivate()
        {
            uint16_t* videoMemory = (uint16_t*)0xb8000;
            x = 40;
            y = 12;
            videoMemory[80 * y + x] = (videoMemory[80 * y + x] & 0x0F00) << 4
                                    | (videoMemory[80 * y + x] & 0xF000) >> 4
                                    | (videoMemory[80 * y + x] & 0x00FF);        
        }
        
        virtual void OnMouseMove(int xoffset, int yoffset)
        {
            static uint16_t* videoMemory = (uint16_t*)0xb8000;
            videoMemory[80 * y + x] = (videoMemory[80 * y + x] & 0x0F00) << 4
                                    | (videoMemory[80 * y + x] & 0xF000) >> 4
                                    | (videoMemory[80 * y + x] & 0x00FF);

            x += xoffset;
            if (x >= 80) {
                x = 79;
            }
            if (x < 0) {
                x = 0;
            }
            y += yoffset;
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
};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    printf("Panix\n");

    GlobalDescriptorTable gdt;
    InterruptManager interruptManager(0x20, &gdt);

    printf("Initializing Hardware, Stage 1\n");
    
    DriverManager driverManager;
    
    KeyboardPrintEventHandler keyboardPrintEventHandler;
    KeyboardDriver keyboard(&interruptManager, &keyboardPrintEventHandler);
    driverManager.addDriver(&keyboard);

    ConsoleMouseEventHandler consoleMouseEventHandler;
    MouseDriver mouse(&interruptManager, &consoleMouseEventHandler);
    driverManager.addDriver(&mouse);

    printf("Initializing Hardware, Stage 2\n");
    driverManager.activateAll();
        
    printf("Initializing Hardware, Stage 3\n");
    interruptManager.activate();

    while(1);
}
