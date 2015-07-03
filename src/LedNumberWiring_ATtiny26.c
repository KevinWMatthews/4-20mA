#include "LedNumberWiring.h"
#include <avr/io.h>
#include "BitManip.h"


//********************************************//
//*** Edit here to change hardware wiring! ***//
//********************************************//
#define WIRINGPIN_LED1 (1<<PB0)
#define WIRINGPIN_LED2 (1<<PB1)
#define WIRINGPIN_LED3 (1<<PB2)
#define WIRINGPIN_LED4 (1<<PB3)

//At the moment only portb pins 3, 4, 5, and 6 are available
void LedNumberWiring_HwSetup(void)
{
  DDRB |= WIRINGPIN_LED1 | WIRINGPIN_LED2 | WIRINGPIN_LED3 | WIRINGPIN_LED4;
  PORTB |= WIRINGPIN_LED1 | WIRINGPIN_LED2 | WIRINGPIN_LED3 | WIRINGPIN_LED4;
}

static uint8_t convertPinToWiringPin(LedNumberWiring_Place pin)
{
  switch (pin)
  {
  case WIRINGLED_UNITS:
    return WIRINGPIN_LED1;
  case WIRINGLED_TENS:
    return WIRINGPIN_LED2;
  case WIRINGLED_HUNDREDS:
    return WIRINGPIN_LED3;
  case WIRINGLED_THOUSANDS:
    return WIRINGPIN_LED4;
  }
}

void LedNumberWiring_SetSelectPin(LedNumberWiring_Place pin)
{
  SBIT(PORTB, WIRINGPIN_LED1);
  SBIT(PORTB, WIRINGPIN_LED2);
  SBIT(PORTB, WIRINGPIN_LED3);
  SBIT(PORTB, WIRINGPIN_LED4);
  if (pin == WIRINGLED_NONE)
  {
    return;
  }
  CBIT(PORTB, convertPinToWiringPin(pin));
}
