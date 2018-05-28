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
 * File:   interrupts.cpp
 * Author: Keeton Feavel, Solar Pepper Studios
 * 
 * Created on May 27, 2018, 7:48 PM
 */

#include "interrupts.h"

uint32_t InterruptManager::handleInterrupt(uint8_t interruptID, uint32_t esp) {
    // Print an interrupt status to the terminal
    kprint_error("[ INTERRUPT ]\n");
    
    
    
    return esp;
}