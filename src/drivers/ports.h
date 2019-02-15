/**
 * File: ports.h
 * Author: Keeton Feavel
 */

#ifndef ports_h
#define ports_h

/**
 * Read a byte from the specified port
 */
unsigned char port_byte_in (unsigned short port);

/**
 * 
 */
void port_byte_out (unsigned short port, unsigned char data);

/**
 * 
 */
unsigned short port_word_in (unsigned short port);

/**
 * 
 */
void port_word_out (unsigned short port, unsigned short data);

#endif /* ports_h */