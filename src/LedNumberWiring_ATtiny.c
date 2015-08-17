#include "LedNumberWiring.h"
#include <avr/io.h>
#include "BitManip.h"



//**************************************//
//*** File-scope Function Prototypes ***//
//**************************************//
static uint8_t convertPinToWiringPin(LedNumberWiring_Place pin);



//************************//
//*** Public Functions ***//
//************************//
void LedNumberWiring_HwSetup(void)
{
  SET_BITS(WIRINGDDR, WIRINGPIN_BITMASK);
  SET_BITS(WIRINGPORT, WIRINGPIN_BITMASK);
}

void LedNumberWiring_SetSelectPin(LedNumberWiring_Place place)
{
  uint8_t pin;

  SET_BITS(WIRINGPORT, WIRINGPIN_BITMASK);
  pin = convertPinToWiringPin(place);
  if (pin == WIRINGPIN_NONE)
  {
    return;
  }
  if (pin == WIRINGPIN_ERROR)
  {
    return;
  }
  CLEAR_BITS(WIRINGPORT, pin);
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
