#include "LedDigitWiring.h"
#include <avr/io.h>
#include "BitManip.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Edit here to change hardware wiring! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#define HWDDR         (DDRB)
#define HWPORT        (PORTB)
#define HWPIN_A       (1<<PB0)
#define HWPIN_B       (1<<PB1)
#define HWPIN_C       (1<<PB2)
#define HWPIN_D       (1<<PB3)
#define HWPIN_E       (1<<PB4)
#define HWPIN_F       (1<<PB5)
#define HWPIN_G       (1<<PB6)
#define HWPIN_DP      (1<<PB7)
#define HWPIN_ERROR   0xff
#define HWPIN_BITMASK (HWPIN_A | HWPIN_B | HWPIN_C | HWPIN_D | HWPIN_E | HWPIN_F | HWPIN_G | HWPIN_DP)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Hardware wiring modification should not cause changes below this point! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//



//**************************************//
//*** File-scope Function Prototypes ***//
//**************************************//
static uint8_t convertPinToWiringPin(LedDigitWiring_Pin pin);



//************************//
//*** Public Functions ***//
//************************//
void LedDigitWiring_HwSetup(void)
{
  //Configure LED pins as outputs
  SET_BITS(HWDDR, HWPIN_BITMASK);
  SET_BITS(HWPORT, HWPIN_BITMASK);
}

void LedDigitWiring_TurnSegmentOn(LedDigitWiring_Pin pin)
{
  uint8_t wiringPin;

  wiringPin = convertPinToWiringPin(pin);
  if (wiringPin == HWPIN_ERROR)
  {
    return;
  }
  CLEAR_BITS(HWPORT, wiringPin);
}

void LedDigitWiring_TurnSegmentOff(LedDigitWiring_Pin pin)
{
  uint8_t wiringPin;

  wiringPin = convertPinToWiringPin(pin);
  if (wiringPin == HWPIN_ERROR)
  {
    return;
  }
  SET_BITS(HWPORT, wiringPin);
}



//*****************************//
//*** File-scope Functions ***//
//*****************************/
static uint8_t convertPinToWiringPin(LedDigitWiring_Pin pin)
{
  switch (pin)
  {
  case PIN_A:
    return HWPIN_A;
  case PIN_B:
    return HWPIN_B;
  case PIN_C:
    return HWPIN_C;
  case PIN_D:
    return HWPIN_D;
  case PIN_E:
    return HWPIN_E;
  case PIN_F:
    return HWPIN_F;
  case PIN_G:
    return HWPIN_G;
  case PIN_DP:
    return HWPIN_DP;
  }
  return HWPIN_ERROR;
}
