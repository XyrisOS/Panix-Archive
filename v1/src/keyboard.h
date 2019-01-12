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
 * File:   keyboard.h
 * Author: Keeton Feavel, Solar Pepper Studios
 *
 * Created on June 3, 2018, 1:30 AM
 */

#ifndef keyboard_h
#define keyboard_h
#include "types.h"
#include "interruptmanager.h"
#include "port.h"
#include "kprint.h"

class KeyboardDriver : public InterruptHandler {
    // Communication ports
    Port_8 data;
    Port_8 command;
public:
    /**
     * 
     * @param mgr
     */
    KeyboardDriver(InterruptManager * mgr);
    
    /**
     * 
     */
    ~KeyboardDriver();
    
    /**
     * 
     * @param esp
     * @return 
     */
    virtual uint32_t HandleInterrupt(uint32_t esp);
};

#endif /* keyboard_h */

