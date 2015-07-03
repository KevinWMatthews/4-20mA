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
  LedDigit digit1, digit2, digit3, digit4;
  int16_t num = 0, i = 0;

  LedDigit_HwSetup();
  LedNumberWiring_Init();

  digit1 = LedDigit_Create();
  digit2 = LedDigit_Create();
  digit3 = LedDigit_Create();
  digit4 = LedDigit_Create();


  number = LedNumber_Create(4);
  LedNumber_AddLedDigit(number, digit1, LED_1);
  LedNumber_AddLedDigit(number, digit2, LED_2);
  LedNumber_AddLedDigit(number, digit3, LED_3);
  LedNumber_AddLedDigit(number, digit4, LED_4);

  LedNumber_SetNumber(number, num);

  while (1)
  {
    LedNumber_ShowNumber(number);
    _delay_ms(2);
    i++;
    if (i == 500)
    {
      i = 0;
      LedNumber_SetNumber(number, num++);
    }
  }
}
