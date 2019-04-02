#ifndef INTERRUPT_HANDLER_HPP
#define INTERRUPT_HANDLER_HPP

#include <types.hpp>
#include <cpu/interrupts/InterruptManager.hpp>

/* Forward declaration */
class InterruptManager;

class InterruptHandler {
    protected:
        uint8_t InterruptNumber;
        InterruptManager* interruptManager;
        InterruptHandler(InterruptManager* interruptManager, uint8_t InterruptNumber);
        ~InterruptHandler();
    public:
        virtual uint32_t handleInterrupt(uint32_t esp);
};

#endif /* INTERRUPT_HANDLER_HPP */