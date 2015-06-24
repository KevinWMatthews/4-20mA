#ifndef MockHw_ATtiny26_H_
#define MockHw_ATtiny26_H_

#include "DataTypes.h"

extern uint8_t DDRA;
extern uint8_t PORTA;

//*** Copied from <avr/io.h> ***//

//Explicitly mock registers
// #define DDRA    _SFR_IO8(0x1A)
// #define PORTA   _SFR_IO8(0x1B)
#define PA0     0
#define PA1     1
#define PA2     2
#define PA3     3
#define PA4     4
#define PA5     5
#define PA6     6
#define PA7     7

#endif
