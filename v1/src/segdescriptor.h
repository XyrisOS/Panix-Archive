/*
 * Copyright (C) 2018 Keeton Feavel, Solar Pepper Studios
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/* 
 * File:   segdescriptor.h
 * Author: Keeton Feavel, Solar Pepper Studios
 *
 * Created on June 1, 2018, 3:48 PM
 */

#ifndef segdescriptor_h
#define segdescriptor_h
#include "types.h"
#include "kprint.h"

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

