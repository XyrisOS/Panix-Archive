/**
 * @file InterruptHandler.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
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
         * @param interruptManager 
         * @param InterruptNumber 
         */
        InterruptHandler(InterruptManager* interruptManager, uint8_t InterruptNumber);
        /**
         * @brief Destroy the Interrupt Handler object
         * 
         */
        ~InterruptHandler();
    public:
        /**
         * @brief 
         * 
         * @param esp 
         * @return uint32_t 
         */
        virtual uint32_t handleInterrupt(uint32_t esp);
};

#endif /* PANIX_INTERRUPT_HANDLER_HPP */