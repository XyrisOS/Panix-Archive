
#ifndef PANIX_PORT_HPP
#define PANIX_PORT_HPP

#include <types.hpp>

class Port {
    protected:
        Port(uint16_t portnumber);
        //virtual ~Port();
        uint16_t portnumber;
};

class Port8Bit : public Port {
    public:
        Port8Bit(uint16_t portnumber);
        //virtual ~Port8Bit();
        virtual uint8_t read();
        virtual void write(uint8_t data);

    protected:
        static uint8_t read8(uint16_t _port);
        static void write8(uint16_t _port, uint8_t _data);
};

class Port8BitSlow : public Port8Bit {
    public:
        Port8BitSlow(uint16_t portnumber);
        //virtual ~Port8BitSlow();
        virtual void write(uint8_t data);

    protected:
        static void write8Slow(uint16_t _port, uint8_t _data);
};

class Port16Bit : public Port {
    public:
        Port16Bit(uint16_t portnumber);
        //virtual ~Port16Bit();
        virtual uint16_t read();
        virtual void write(uint16_t data);

    protected:
        static uint16_t read16(uint16_t _port);
        static void write16(uint16_t _port, uint16_t _data);
};

class Port32Bit : public Port {
    public:
        Port32Bit(uint16_t portnumber);
        //virtual ~Port32Bit();
        virtual uint32_t read();
        virtual void write(uint32_t data);

    protected:
        static uint32_t read32(uint16_t _port);
        static void write32(uint16_t _port, uint32_t _data);
};

#endif /* PANIX_PORT_HPP */