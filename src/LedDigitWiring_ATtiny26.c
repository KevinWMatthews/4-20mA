#include "LedDigitWiring.h"
#include <avr/io.h>
#include "BitManip.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Edit here to change hardware wiring! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#define WIRINGPIN_A     (1<<PA0)
#define WIRINGPIN_B     (1<<PA1)
#define WIRINGPIN_C     (1<<PA2)
#define WIRINGPIN_D     (1<<PA3)
#define WIRINGPIN_E     (1<<PA4)
#define WIRINGPIN_F     (1<<PA5)
#define WIRINGPIN_G     (1<<PA6)
#define WIRINGPIN_DP    (1<<PA7)
#define WIRINGPIN_ERROR 0xff
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
  DDRA = WIRINGPIN_A | WIRINGPIN_B | WIRINGPIN_C | WIRINGPIN_D | WIRINGPIN_E | WIRINGPIN_F | WIRINGPIN_G |WIRINGPIN_DP;
  PORTA = 0xff;
}

void LedDigitWiring_TurnSegmentOn(LedDigitWiring_Pin pin)
{
  uint8_t wiringPin;

  wiringPin = convertPinToWiringPin(pin);
  if (wiringPin == WIRINGPIN_ERROR)
  {
    return;
  }
  CBIT(PORTA, wiringPin);
}

void LedDigitWiring_TurnSegmentOff(LedDigitWiring_Pin pin)
{
  uint8_t wiringPin;

  wiringPin = convertPinToWiringPin(pin);
  if (wiringPin == WIRINGPIN_ERROR)
  {
    return;
  }
  SBIT(PORTA, wiringPin);;
}



//*****************************//
//*** File-scope Functions ***//
//*****************************/
static uint8_t convertPinToWiringPin(LedDigitWiring_Pin pin)
{
  switch (pin)
  {
  case PIN_A:
    return WIRINGPIN_A;
  case PIN_B:
    return WIRINGPIN_B;
  case PIN_C:
    return WIRINGPIN_C;
  case PIN_D:
    return WIRINGPIN_D;
  case PIN_E:
    return WIRINGPIN_E;
  case PIN_F:
    return WIRINGPIN_F;
  case PIN_G:
    return WIRINGPIN_G;
  case PIN_DP:
    return WIRINGPIN_DP;
  }
  return WIRINGPIN_ERROR;
}
