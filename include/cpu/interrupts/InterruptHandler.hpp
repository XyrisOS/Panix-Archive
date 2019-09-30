/**
 * @file InterruptHandler.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief The interrupt handler is an interface class that
 * allows other classes to register themselves as having a
 * callback for a specific interrupt (or possibly exception).
 * All a class has to do is add `public InterruptHandler` to
 * their class declaration and then call the constructor with
 * the interrupt manager and interrupt value it wants to
 * register. The handleInterupt() function must be implemented
 * in said class.
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_INTERRUPT_HANDLER_HPP
#define PANIX_INTERRUPT_HANDLER_HPP

#include <types.hpp>
#include <cpu/interrupts/InterruptManager.hpp>

/* Forward declaration */
class InterruptManager;

class InterruptHandler {
    protected:
        uint8_t InterruptNumber;
        InterruptManager* interruptManager;
        /**
         * @brief Construct a new Interrupt Handler object
         * 
         * @param interruptManager Kernel interrupt manager
         * @param InterruptNumber Interrupt number to be registered for callback.
         */
        InterruptHandler(InterruptManager* interruptManager, uint8_t InterruptNumber);
        /**
         * @brief Destroy the Interrupt Handler object
         * 
         */
        ~InterruptHandler();
        
    public:
        /**
         * @brief Interface function that acts as a callback for a registered interrupt.
         * When the interrupt manager gets an interrupt of a given number, it will call
         * this function in all classes which implement the InterruptManager interface.
         * 
         * @param esp Stack pointer. Must be returned.
         * @return uint32_t Returned stack pointer.
         */
        virtual uint32_t handleInterrupt(uint32_t esp);
};

#endif /* PANIX_INTERRUPT_HANDLER_HPP */