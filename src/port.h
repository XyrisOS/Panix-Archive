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
    /**
     * Port "master" constructor
     * @param port Port address
     */
    Port(uint16_t port);
    
    /**
     * Port "master" deconstructor
     */
    ~Port();
    // Port ID
    uint16_t portnumber;
};

class Port_8 : public Port {
public:
    
    /**
     * Constructs an 8-bit message port.
     * @param port
     */
    Port_8(uint8_t port);
    
    /**
     * Deconstructor for the 8-bit message port.
     */
    ~Port_8();
    /**
     * Write an 8-bit message.
     * @param msg 8-bit message.
     */
    virtual void write(uint8_t msg);
    
    /**
     * Read a message.
     * @return Returns an 8-bit message.
     */
    virtual uint8_t read();
};

/**
 * Slower version of Port_8
 */
class Port_8_Slow : public Port_8 {
public:
    
    /**
     * Constructs a slow 8-bit message port.
     * @param port
     */
    Port_8_Slow(uint8_t port);
    
    /**
     * Deconstructor for the slow 8-bit message port.
     */
    ~Port_8_Slow();
    
    /**
     * Write an 8-bit message slowly.
     * @param msg 8-bit message.
     */
    virtual void write(uint8_t msg);
};

class Port_16 : public Port {
public:
    
    /**
     * Constructs a 16-bit message port.
     * @param port 16-bit message port.
     */
    Port_16(uint16_t port);
    
    /**
     * Deconstructor for the 16-bit message port.
     */
    ~Port_16();
    
    /**
     * Write a 16-bit message.
     * @param msg 16-bit message.
     */
    virtual void write(uint16_t msg);
    
    /**
     * Read a 16-bit message.
     * @return 16-bit message.
     */
    virtual uint16_t read();
};

class Port_32 : public Port {
public:
    
    /**
     * Constructs a 32-bit message port.
     * @param port 32-bit message port.
     */
    Port_32(uint32_t port);
    
    /**
     * Deconstructor for the 32-bit message port.
     */
    ~Port_32();
    
    /**
     * Writes a 32-bit message.
     * @param msg 32-bit message.
     */
    virtual void write(uint32_t msg);
    
    /**
     * Reads a 32-bit message.
     * @return 32-bit message.
     */
    virtual uint32_t read();
};

#endif /* port_h */