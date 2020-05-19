/**
 * @file InterruptHandler.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#include <cpu/interrupts/InterruptHandler.hpp>

InterruptHandler::InterruptHandler(InterruptManager* interruptManager, uint8_t InterruptNumber) {
    this->InterruptNumber = InterruptNumber;
    this->interruptManager = interruptManager;
    interruptManager->handlers[InterruptNumber] = this;
}

InterruptHandler::~InterruptHandler() {
    if (interruptManager->handlers[InterruptNumber] == this) {
        interruptManager->handlers[InterruptNumber] = 0;
    }
}

uint32_t InterruptHandler::handleInterrupt(uint32_t esp) {
    // This is technically a stubbed function. This handleInterrupt basically acts
    // as an interface. So, when you have a device or something that needs access
    // to an interrupt it should implement the InterruptHandler class and have a 
    // overwritten handleInterrupt function in it's own class. Mouse and Keyboard
    // are good examples of this.
    return esp;
}