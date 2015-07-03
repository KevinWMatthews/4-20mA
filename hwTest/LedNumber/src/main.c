#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 1000000UL     /* 8MHz internal crystal */
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "LedNumber.h"
#include "LedDigit.h"


int main(void)
{
  LedNumber number;
  LedDigit digit1, digit2, digit3, digit4;
  int16_t num = 0, i = 0;

  LedDigit_HwSetup();
  LedNumber_HwSetup();

  digit1 = LedDigit_Create();
  digit2 = LedDigit_Create();
  digit3 = LedDigit_Create();
  digit4 = LedDigit_Create();


  number = LedNumber_Create(4);
  LedNumber_AddLedDigit(number, digit1, LED_UNITS);
  LedNumber_AddLedDigit(number, digit2, LED_TENS);
  LedNumber_AddLedDigit(number, digit3, LED_HUNDREDS);
  LedNumber_AddLedDigit(number, digit4, LED_THOUSANDS);

  LedNumber_SetNumber(number, 1234);

  while (1)
  {
    LedNumber_ShowNumber(number);
    _delay_ms(500);
    // i++;
    // if (i == 100)
    // {
    //   i = 0;
    //   LedNumber_SetNumber(number, num++);
    // }
  }
}
