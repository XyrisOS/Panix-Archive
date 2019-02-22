#ifndef TIMER_H
#define TIMER_H

#include "../kernel/util/util.h"
#include "../drivers/ports.h"
#include "./types.h"

void initTimer(uint32_t freq);

#endif /* TIMER_H */