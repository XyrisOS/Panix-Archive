#ifndef PANIX_KEYBOARD_DRIVER_HPP
#define PANIX_KEYBOARD_DRIVER_HPP

#include <types.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <cpu/port/Port.hpp>
#include <drivers/keyboard/KeyboardEventHandler.hpp>
#include <drivers/Driver.hpp>
#include <libc/kprint.hpp>
#include <libc/string.hpp>
#include <kernel/shell/shell.hpp>

class KeyboardEventHandler;

#define PANIX_BACKSPACE 0x0E
#define PANIX_ENTER 0x1C
#define PANIX_LEFT_SHIFT 0x2A
#define PANIX_RIGHT_SHIFT 0x36
#define PANIX_UP_ARROW 0x48
#define PANIX_SCANCODE_MAX 57

class KeyboardDriver : public InterruptHandler, public Driver {
    private:
        Port8Bit dataPort;
        Port8Bit commandPort;
        KeyboardEventHandler* keyboardEventHandler;
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

        /**
         * @brief Kernel level shell to handle input
         * 
         */
        shell *console;
    public:
        /**
         * @brief Construct a new Keyboard Driver object
         * 
         * @param interruptManager 
         * @param keyboardEventHandler 
         */
        KeyboardDriver(InterruptManager* interruptManager, KeyboardEventHandler* keyboardEventHandler);
        /**
         * @brief Destroy the Keyboard Driver object
         * 
         */
        ~KeyboardDriver();
        /**
         * @brief 
         * 
         * @param esp 
         * @return uint32_t 
         */
        virtual uint32_t handleInterrupt(uint32_t esp);
        /**
         * @brief 
         * 
         */
        virtual void activate();

        /**
         * @brief Sets the keyboard driver kernel shell object
         * 
         * @param sh Kernel shell
         */
        void setConsole(shell* sh);
};

#endif /* PANIX_KEYBOARD_DRIVER_HPP */