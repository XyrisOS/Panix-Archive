#ifndef TIMER_H
#define TIMER_H

#include "../drivers/screen.h"
#include "../libc/string.h"
#include "isr.h"
#include "ports.h"
#include "types.h"

void initTimer(uint32_t frequency);

#endif /* TIMER_H */