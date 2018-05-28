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
     * 
     * @param port
     */
    Port(uint16_t port);
    
    /**
     * 
     */
    ~Port();
    // Port ID
    uint16_t portnumber;
};

class Port_8 : public Port {
protected:
    
    /**
     * 
     * @param port
     */
    Port_8(uint8_t port);
    
    /**
     * 
     */
    ~Port_8();
    
    /**
     * 
     * @param msg
     */
    virtual void write(uint8_t msg);
    
    /**
     * 
     * @return 
     */
    virtual uint8_t read();
};

/**
 * Slower version of Port_8 for compatibility
 */
class Port_8_Slow : public Port_8 {
protected:
    
    /**
     * 
     * @param port
     */
    Port_8_Slow(uint8_t port);
    
    /**
     * 
     */
    ~Port_8_Slow();
    
    /**
     * 
     * @param msg
     */
    virtual void write(uint8_t msg);
};

class Port_16 : public Port {
protected:
    
    /**
     * 
     * @param port
     */
    Port_16(uint16_t port);
    
    /**
     * 
     */
    ~Port_16();
    
    /**
     * 
     * @param msg
     */
    virtual void write(uint16_t msg);
    
    /**
     * 
     * @return 
     */
    virtual uint16_t read();
};

class Port_32 : public Port {
protected:
    
    /**
     * 
     * @param port
     */
    Port_32(uint32_t port);
    
    /**
     * 
     */
    ~Port_32();
    
    /**
     * 
     * @param msg
     */
    virtual void write(uint32_t msg);
    
    /**
     * 
     * @return 
     */
    virtual uint32_t read();
};

#endif /* port_h */