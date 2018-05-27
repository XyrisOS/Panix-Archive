//  Memory Segment Descriptor for the EDIX kernel.
//  segdescriptor.h
//  EDIX
//
//  Created by Keeton Feavel on 5/24/18.
//  (c) Solar Pepper Studios 2018, all rights reserved.

#ifndef segdescriptor_h
#define segdescriptor_h

#include "types.h"
#include "kprint.h"

// Declare Segment Descriptor Subclass

class SegmentDescriptor {
public:
    // Constructor
    SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags);
    uint32_t Base();
    uint32_t Limit();
private:
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t base_hi;
    uint8_t type;
    uint8_t limit_hi_flags;
    uint8_t base_vhi;

} __attribute__((packed));

#endif /* segdescriptor_h */