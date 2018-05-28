//  Memory Segment Descriptor for the EDIX kernel.
//  segdescriptor.h
//  EDIX
//
//  Created by Keeton Feavel on 5/26/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#ifndef segdescriptor_h
#define segdescriptor_h

#include "types.h"
#include "kprint.h"

// Declare Segment Descriptor Subclass

class SegmentDescriptor {
public:

    /**
     * Segment Descriptor constructor
     * @param base Address base bits
     * @param limit Address limit bits
     * @param flags Address flags
     */
    SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags);

    /**
     * Returns the memory address base bits
     * @return memory address base bits as a 32 bit integer
     */
    uint32_t Base();

    /**
     * Returns the memory address limit bits
     * @return memory address limit bits as a 32 bit integer
     */
    uint32_t Limit();
private:
    // Class variables
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t base_hi;
    uint8_t type;
    uint8_t limit_hi_flags;
    uint8_t base_vhi;

} __attribute__ ((packed));

#endif /* segdescriptor_h */