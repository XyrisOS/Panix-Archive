/**
 * @file ports.h
 * @author Keeton Feavel and James Osborne
 * @brief Ports header file. Provides a class
 * for getting and setting values at different ports.
 * @version 0.1
 * @date 2019-02-24
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef PORTS_H
#define PORTS_H

#include "../type.h"

namespace cpu {
    class Ports {
        public:
            /**
             * @brief Get the byte at the specified port
             * 
             * @param port Port to receive data from
             * @return uint8_t Data from specified port
             */
            static uint8_t getPortByte(uint16_t port);

            /**
             * @brief Get the word at the specified port
             * 
             * @param port Port to receive data from
             * @return uint16_t Data from specified port
             */
            static uint16_t getPortWord(uint16_t port);

            /**
             * @brief Set the byte at the specified port
             * 
             * @param port Port to set with data
             * @param data Data to set port with
             */
            static void setPortByte(uint16_t port, uint8_t data);

            /**
             * @brief Set the word at the specified port
             * 
             * @param port Port to set with data
             * @param data Data to set port with
             */
            static void setPortWord(uint16_t port, uint16_t data);
    };
}

#endif /* PORTS_H */