/**
 * @file Port.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief Ports header file. Provides a class
 * for getting and setting values at different ports.
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_PORT_HPP
#define PANIX_PORT_HPP

#include <types.hpp>
// TODO: Refactor some of these functions to remove the extra read / write protected funcs.
class Port {
    protected:
        /**
         * @brief Construct a new Port object
         * 
         * @param portnumber Port number to be used
         */
        explicit Port(uint16_t portnumber);
        //virtual ~Port();
        uint16_t portnumber;
};

class PortByte : public Port {
    public:
        /**
         * @brief Construct a new Port Byte object
         * 
         * @param portnumber Port number to be used
         */
        explicit PortByte(uint16_t portnumber);
        //virtual ~PortByte();
        /**
         * @brief Read in a byte from the port specified by the constructor.
         * 
         * @return uint8_t Byte read in from the port.
         */
        virtual uint8_t read();
        /**
         * @brief Writes a byte to the port specified by the constructor.
         * 
         * @param data Byte to write to the port.
         */
        virtual void write(uint8_t data);

    protected:
        static uint8_t read8(uint16_t _port);
        static void write8(uint16_t _port, uint8_t _data);
};

class PortByteSlow : public PortByte {
    public:
        /**
         * @brief Construct a new Port Byte Slow object
         * 
         * @param portnumber 
         */
        explicit PortByteSlow(uint16_t portnumber);
        //virtual ~PortByteSlow();
        /**
         * @brief Writes a byte slowly to the port specified by the constructor.
         * 
         * @param data Byte to write to the port.
         */
        virtual void write(uint8_t data);

    protected:
        static void write8Slow(uint16_t _port, uint8_t _data);
};

class PortWord : public Port {
    public:
        /**
         * @brief Construct a new Port Word object
         * 
         * @param portnumber 
         */
        explicit PortWord(uint16_t portnumber);
        //virtual ~PortWord();
        /**
         * @brief Read in a word from the port specified by the constructor.
         * 
         * @return uint16_t Word read in from the port.
         */
        virtual uint16_t read();
        /**
         * @brief Writes a word to the port specified by the constructor.
         * 
         * @param data Word to write to the port.
         */
        virtual void write(uint16_t data);

    protected:
        static uint16_t read16(uint16_t _port);
        static void write16(uint16_t _port, uint16_t _data);
};

class PortLong : public Port {
    public:
        /**
         * @brief Construct a new Port Long object
         * 
         * @param portnumber 
         */
        explicit PortLong(uint16_t portnumber);
        //virtual ~PortLong();
        /**
         * @brief Read in a long from the port specified by the constructor.
         * 
         * @return uint32_t Long read in from the port.
         */
        virtual uint32_t read();
        /**
         * @brief Writes a long to the port specified by the constructor.
         * 
         * @param data Long to write to the port.
         */
        virtual void write(uint32_t data);

    protected:
        static uint32_t read32(uint16_t _port);
        static void write32(uint16_t _port, uint32_t _data);
};

#endif /* PANIX_PORT_HPP */