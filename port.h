//  Port manager for the EDIX kernel.
//  port.h
//  EDIX
//
//  Created by Keeton Feavel on 5/25/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#ifndef port_h
#define port_h
#include "types.h"

class Port {
protected:
    // Constructor
    Port(uint16_t port);
    // Destructor
    ~Port();
    // Port ID
    uint16_t portnumber;
};

class Port_8 : public Port {
protected:
    // Constructor
    Port_8(uint8_t port);
    // Destructor
    ~Port_8();
    virtual void write(uint8_t msg);
    virtual uint8_t read();
};

/**
 * Slower version of Port_8 for compatibility
 */
class Port_8_Compatibility : public Port_8 {
protected:
    // Constructor
    Port_8_Compatibility(uint8_t port);
    // Destructor
    ~Port_8_Compatibility();
    virtual void write(uint8_t msg);
};

class Port_16 : public Port {
protected:
    // Constructor
    Port_16(uint16_t port);
    // Destructor
    ~Port_16();
    virtual void write(uint16_t msg);
    virtual uint16_t read();
};

class Port_32 : public Port {
protected:
    // Constructor
    Port_32(uint32_t port);
    // Destructor
    ~Port_32();
    virtual void write(uint32_t msg);
    virtual uint32_t read();
};

#endif /* port_h */