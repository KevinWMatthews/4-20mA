#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 1000000UL     /* 8MHz internal crystal */
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "LedDigit.h"
#include "LedDigitWiring.h"

int main(void)
{
  LedDigitWiring_Init();
  int i = -1;
  while (1)
  {
    _delay_ms(100);
    i++;
    switch (i)
    {
    case 0:
      LedDigitWiring_TurnSegmentOff(PIN_F);
      LedDigitWiring_TurnSegmentOn(PIN_A);
      break;
    case 1:
      LedDigitWiring_TurnSegmentOff(PIN_A);
      LedDigitWiring_TurnSegmentOn(PIN_B);
      break;
    case 2:
      LedDigitWiring_TurnSegmentOff(PIN_B);
      LedDigitWiring_TurnSegmentOn(PIN_G);
      break;
    case 3:
      LedDigitWiring_TurnSegmentOff(PIN_G);
      LedDigitWiring_TurnSegmentOn(PIN_E);
      break;
    case 4:
      LedDigitWiring_TurnSegmentOff(PIN_E);
      LedDigitWiring_TurnSegmentOn(PIN_D);
      break;
    case 5:
      LedDigitWiring_TurnSegmentOff(PIN_D);
      LedDigitWiring_TurnSegmentOn(PIN_C);
      break;
    case 6:
      LedDigitWiring_TurnSegmentOff(PIN_C);
      LedDigitWiring_TurnSegmentOn(PIN_G);
      break;
    case 7:
      LedDigitWiring_TurnSegmentOff(PIN_G);
      LedDigitWiring_TurnSegmentOn(PIN_F);
      break;
    case 8:
      LedDigitWiring_TurnSegmentOff(PIN_F);
      LedDigitWiring_TurnSegmentOn(PIN_A);
      i = 0;
      break;
    }
  }
}

//int main(void)
//{
  //LedDigit digit;
  //LedDigit_Value currentDigit;
//
  //LedDigitWiring_Init();
//
  //digit = LedDigit_Create();
//
  //currentDigit = ZERO;
//
  //while (1)
  //{
    //_delay_ms(1000);
    //LedDigit_SetDigit(digit, currentDigit);
    //LedDigit_UpdateLed(digit);
    //if (currentDigit == NINE)
    //{
      //currentDigit = ZERO;
      //if (LedDigit_IsDecimalShown(digit))
      //{
        //LedDigit_ClearDecimal(digit);
      //}
      //else
      //{
        //LedDigit_SetDecimal(digit);
      //}
    //}
    //else
    //{
      //currentDigit += 1;
    //}
  //}
//}
