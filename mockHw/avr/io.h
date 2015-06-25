#ifndef io_H_
#define io_H_

#include "DataTypes.h"

//Explicitly mock registers
extern uint8_t DDRA;
extern uint8_t DDRB;
extern uint8_t PORTA;
extern uint8_t PORTB;

//*** Copied from <avr/io.h> ***//

//*** GPIO lines ***//
// #define DDRA    _SFR_IO8(0x1A)
// #define DDRB    _SFR_IO8(0x17)

// #define PORTA   _SFR_IO8(0x1B)
#define PA0     0
#define PA1     1
#define PA2     2
#define PA3     3
#define PA4     4
#define PA5     5
#define PA6     6
#define PA7     7

// #define PORTB   _SFR_IO8(0x18)
#define PB0     0
#define PB1     1
#define PB2     2
#define PB3     3
#define PB4     4
#define PB5     5
#define PB6     6
#define PB7     7



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
