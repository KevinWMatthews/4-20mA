#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 1000000UL     /* 8MHz internal crystal divided by 8 */
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

  DDRB = 0x03;

  while (1)
  {
    PORTB = 0x01;
    LedDigit_SetDigit(digit, currentDigit);
    LedDigit_UpdateLed(digit);
    _delay_ms(500);

    PORTB = 0x02;
    _delay_ms(500);

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
