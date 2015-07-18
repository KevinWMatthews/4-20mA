#include "LedNumberWiring.h"
#include <avr/io.h>
#include "BitManip.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Edit here to change hardware wiring! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//Currently only 4 LEDs are supported
#define WIRINGPIN_NONE    0
#define WIRINGPIN_LED1    (1<<PB0)
#define WIRINGPIN_LED2    (1<<PB1)
#define WIRINGPIN_LED3    (1<<PB2)
#define WIRINGPIN_LED4    (1<<PB3)
#define WIRINGPIN_ERROR   0xff
#define WIRINGPIN_BITMASK (WIRINGPIN_LED1 | WIRINGPIN_LED2 | WIRINGPIN_LED3 | WIRINGPIN_LED4)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Edit here to change hardware wiring! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//



//**************************************//
//*** File-scope Function Prototypes ***//
//**************************************//
static uint8_t convertPinToWiringPin(LedNumberWiring_Place pin);



//************************//
//*** Public Functions ***//
//************************//
void LedNumberWiring_HwSetup(void)
{
  SET_BITS(DDRB, WIRINGPIN_BITMASK);
  SET_BITS(PORTB, WIRINGPIN_BITMASK);
}

void LedNumberWiring_SetSelectPin(LedNumberWiring_Place place)
{
  uint8_t pin;

  SET_BITS(PORTB, WIRINGPIN_BITMASK);
  pin = convertPinToWiringPin(place);
  if (pin == WIRINGPIN_NONE)
  {
    return;
  }
  if (pin == WIRINGPIN_ERROR)
  {
    return;
  }
  CLEAR_BITS(PORTB, pin);
}



//****************************//
//*** File-scope Functions ***//
//****************************//
static uint8_t convertPinToWiringPin(LedNumberWiring_Place pin)
{
  switch (pin)
  {
  case WIRINGLED_NONE:
    return WIRINGPIN_NONE;

  case WIRINGLED_UNITS:
    return WIRINGPIN_LED1;

  case WIRINGLED_TENS:
    return WIRINGPIN_LED2;

  case WIRINGLED_HUNDREDS:
    return WIRINGPIN_LED3;

  case WIRINGLED_THOUSANDS:
    return WIRINGPIN_LED4;

  case WIRINGLED_UPPER_BOUND:
    return WIRINGPIN_ERROR;
  }
  return WIRINGPIN_ERROR;
}
