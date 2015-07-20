#include "io.h"

//*** CPU prescaler ***//
uint8_t CLKPR;

//*** ADC control ***//
uint8_t ADCL;
uint8_t ADCH;
uint8_t ADCSR;
uint8_t ADMUX;

//*** GPIO lines ***//
uint8_t DDRA;
uint8_t DDRB;
uint8_t PORTA;
uint8_t PORTB;

//*** ATtiny861 Timer/Counter 0 ***//
uint8_t TCCR0A;
uint8_t TCCR0B;
uint8_t OCR0A;
uint8_t TIMSK;


//*** Global Interrupts ***//
uint8_t SREG;
