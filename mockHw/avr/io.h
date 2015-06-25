#ifndef io_H_
#define io_H_

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


//ADMUX - ADC Multiplexer Selection Register
#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX4  4
#define MUX3  3
#define MUX2  2
#define MUX1  1
#define MUX0  0

//ADCSR - ADC Control and Status Register
#define ADEN  7
#define ADSC  6
#define ADIF  5
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

#endif
