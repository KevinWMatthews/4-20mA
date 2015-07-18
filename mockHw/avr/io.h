#ifndef io_H_
#define io_H_

#include "DataTypes.h"


//This mocking system is designed for a single ATtiny chip only.
//We'll need to (re)implement the layers found in the avr headers
//if we wish to support multiple chips.


//*** ADC control ***//
// #define ADCL    _SFR_IO8(0x04)
// #define ADCH    _SFR_IO8(0x05)
extern uint8_t ADCL;
extern uint8_t ADCH;

//ADCSR - ADC Control and Status Register
// #define ADCSR   _SFR_IO8(0x06)
extern uint8_t ADCSR;
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
extern uint8_t ADMUX;
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
extern uint8_t DDRA;


// #define PORTA   _SFR_IO8(0x1B)
extern uint8_t PORTA;
#define PA0     0
#define PA1     1
#define PA2     2
#define PA3     3
#define PA4     4
#define PA5     5
#define PA6     6
#define PA7     7

// #define DDRB    _SFR_IO8(0x17)
extern uint8_t DDRB;

// #define PORTB   _SFR_IO8(0x18)
extern uint8_t PORTB;
#define PB0     0
#define PB1     1
#define PB2     2
#define PB3     3
#define PB4     4
#define PB5     5
#define PB6     6
#define PB7     7


//*** ATtiny861 Timer/Counter 0 ***//
// #define TCCR0A  _SFR_IO8(0x15)
extern uint8_t TCCR0A;
#define CTC0    0
#define ACIC0   3
#define ICES0   4
#define ICNC0   5
#define ICEN0   6
#define TCW0    7

// #define TCCR0B  _SFR_IO8(0x33)
extern uint8_t TCCR0B;
#define CS00    0
#define CS01    1
#define CS02    2
#define PSR0    3
#define TSM     4

// #define OCR0A   _SFR_IO8(0x13)
extern uint8_t OCR0A;

// #define TIMSK   _SFR_IO8(0x39)
extern uint8_t TIMSK;
#define TICIE0  0
#define TOIE0   1
#define TOIE1   2
#define OCIE0B  3
#define OCIE0A  4
#define OCIE1B  5
#define OCIE1A  6
#define OCIE1D  7



//*** Global Interrupts ***//
//I believe that is is defined in common.h and included by io.h
/* Status Register */
// #ifndef SREG
// #  if __AVR_ARCH__ >= 100
// #    define SREG _SFR_MEM8(0x3F)
// #  else
// #    define SREG _SFR_IO8(0x3F)
// #  endif
// #endif
extern uint8_t SREG;



#endif
