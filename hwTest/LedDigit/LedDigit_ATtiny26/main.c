#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 8000000UL     /* 8MHz internal crystal */
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "LedDigit.h"
#include "LedDigitWiring.h"



int main(void)
{
  LedDigit digit;
  LedDigit_Value currentDigit;

  LedDigitWiring_HwSetup();

  digit = LedDigit_Create();

  currentDigit = ZERO;

  while (1)
  {
    _delay_ms(1000);
    LedDigit_SetDigit(digit, currentDigit);
    LedDigit_UpdateLed(digit);
    if (currentDigit == NINE)
    {
      currentDigit = ZERO;
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
