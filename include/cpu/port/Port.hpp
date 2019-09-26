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

class Port {
    protected:
        Port(uint16_t portnumber);
        //virtual ~Port();
        uint16_t portnumber;
};

class PortByte : public Port {
    public:
        PortByte(uint16_t portnumber);
        //virtual ~PortByte();
        virtual uint8_t read();
        virtual void write(uint8_t data);

    protected:
        static uint8_t read8(uint16_t _port);
        static void write8(uint16_t _port, uint8_t _data);
};

class PortByteSlow : public PortByte {
    public:
        PortByteSlow(uint16_t portnumber);
        //virtual ~PortByteSlow();
        virtual void write(uint8_t data);

    protected:
        static void write8Slow(uint16_t _port, uint8_t _data);
};

class PortWord : public Port {
    public:
        PortWord(uint16_t portnumber);
        //virtual ~PortWord();
        virtual uint16_t read();
        virtual void write(uint16_t data);

    protected:
        static uint16_t read16(uint16_t _port);
        static void write16(uint16_t _port, uint16_t _data);
};

class PortLong : public Port {
    public:
        PortLong(uint16_t portnumber);
        //virtual ~PortLong();
        virtual uint32_t read();
        virtual void write(uint32_t data);

    protected:
        static uint32_t read32(uint16_t _port);
        static void write32(uint16_t _port, uint32_t _data);
};

#endif /* PANIX_PORT_HPP */