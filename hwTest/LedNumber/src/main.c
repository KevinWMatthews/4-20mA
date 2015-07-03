#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 1000000UL     /* 8MHz internal crystal */
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "LedNumber.h"
#include "LedNumberWiring.h"
#include "LedDigit.h"
#include "LedDigitWiring.h"


int main(void)
{
  LedNumber number;
  LedDigit digit1, digit2;

  LedDigit_HwSetup();
  LedNumberWiring_Init();

  digit1 = LedDigit_Create();
  digit2 = LedDigit_Create();


  number = LedNumber_Create(2);
  LedNumber_AddLedDigit(number, digit1, LED_1);
  LedNumber_AddLedDigit(number, digit2, LED_2);

  LedNumber_SetNumber(number, 42);

  while (1)
  {
    LedNumber_ShowNumber(number);
    _delay_ms(10);
  }
}
