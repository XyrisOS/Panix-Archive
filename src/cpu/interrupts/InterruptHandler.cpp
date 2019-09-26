/**
 * @file InterruptHandler.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
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
    return esp;
}