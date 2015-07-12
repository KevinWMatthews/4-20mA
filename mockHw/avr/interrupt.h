#ifndef interrupt_H
#define interrupt_H

#include <avr/io.h>
#include "BitManip.h"


//Manually mock chip-specific macros
#define ISR(name) void InterruptHandler_##name(void)

#define sei() SET_BIT_NUMBER(SREG, 7)
#define cli() CLEAR_BIT_NUMBER(SREG, 7)


#endif
