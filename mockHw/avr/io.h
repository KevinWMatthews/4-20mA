#ifndef io_H_
#define io_H_

#include "DataTypes.h"

//Explicitly mock registers
//*** ADC control ***//
extern uint8_t ADCL;
extern uint8_t ADCH;
extern uint8_t ADCSR;
extern uint8_t ADMUX;

//*** GPIO lines ***//
extern uint8_t DDRA;
extern uint8_t DDRB;
extern uint8_t PORTA;
extern uint8_t PORTB;



//*** Copied from <avr/io.h> ***//

//*** ADC control ***//
// #define ADCL    _SFR_IO8(0x04)
// #define ADCH    _SFR_IO8(0x05)

//ADCSR - ADC Control and Status Register
// #define ADCSR   _SFR_IO8(0x06)
#define ADPS0   0
#define ADPS1   1
#define ADPS2   2
#define ADIE    3
#define ADIF    4
#define ADFR    5
#define ADSC    6
#define ADEN    7

//ADMUX - ADC Multiplexer Selection Register
// #define ADMUX   _SFR_IO8(0x07)
#define MUX0    0
#define MUX1    1
#define MUX2    2
#define MUX3    3
#define MUX4    4
#define ADLAR   5
#define REFS0   6
#define REFS1   7



//*** GPIO lines ***//
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

// #define DDRB    _SFR_IO8(0x17)

// #define PORTB   _SFR_IO8(0x18)
#define PB0     0
#define PB1     1
#define PB2     2
#define PB3     3
#define PB4     4
#define PB5     5
#define PB6     6
#define PB7     7

#endif
