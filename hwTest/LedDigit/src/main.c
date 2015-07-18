#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 1000000UL     /* 8MHz internal crystal divided by 8 */
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "LedDigit.h"



int main(void)
{
  LedDigit digit;
  LedDigit_Value currentDigit;

  LedDigit_HwSetup();
  digit = LedDigit_Create();
  currentDigit = ZERO;

  while (1)
  {
    LedDigit_SetDigit(digit, currentDigit);
    LedDigit_UpdateLed(digit);

    _delay_ms(500);

    if (currentDigit == NINE)
    {
      currentDigit = ZERO;
      //Toggle decimal point at rollover
      if (LedDigit_IsDecimalShown(digit))
      {
        LedDigit_ClearDecimal(digit);
      }
      else
      {
        LedDigit_SetDecimal(digit);
      }
    }
    else
    {
      currentDigit += 1;
    }
  }
}
