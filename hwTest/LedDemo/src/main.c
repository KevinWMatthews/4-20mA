#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 8000000UL     /* 8MHz internal crystal */
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "BitManip.h"

//Write to memory address PORTA
//PA0 through PA7 are the bits contained in this address
#define LED_1 (1<<PA0)
#define LED_2 (1<<PA1)
#define LED_3 (1<<PA2)
#define LED_4 (1<<PA3)
#define LED_5 (1<<PA4)
#define LED_6 (1<<PA5)
#define LED_7 (1<<PA6)
#define LED_8 (1<<PA7)

int main(void)
{
  //Configure LED pins as outputs
  DDRA = (LED_1) | (LED_2) | (LED_3) | (LED_4) | (LED_5) | (LED_6) | (LED_7) | (LED_8);

  while (1)
  {
    _delay_ms(2000);
    SBI(PORTA, LED_1);
    _delay_ms(2000);
    CBI(PORTA, LED_1);
  }
}
