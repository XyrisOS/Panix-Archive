#ifndef KEYBOARD_DRIVER_HPP
#define KEYBOARD_DRIVER_HPP

#include <types.hpp>
#include <cpu/interrupts/InterruptManager.hpp>
#include <cpu/Port/Port.hpp>
#include <drivers/keyboard/KeyboardEventHandler.hpp>
#include <drivers/Driver.hpp>
#include <libc/kprint.hpp>
#include <libc/string.hpp>

class KeyboardEventHandler;

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define UP_ARROW 0x48
#define SCANCODE_MAX 57

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
};

#endif /* KEYBOARD_DRIVER_HPP */