#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 1000000UL     /* 8MHz internal crystal */
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "LedNumber.h"


int main(void)
{
  LedNumber number;
  int16_t num = 0, i = 0;

  LedNumber_HwSetup();

  number = LedNumber_Create(LED_THOUSANDS);

  while (1)
  {
    LedNumber_SetNumber(number, num);
    LedNumber_ShowNumber(number);
    _delay_ms(2);
    i++;
    if (i >= 25)
    {
      i = 0;
      num++;
      if (num >= 9999)
      {
        num = 0;
      }
    }
  }
}
