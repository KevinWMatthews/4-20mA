#ifndef F_CPU               /* Used by <util/delay.h> */
#define F_CPU 8000000UL     /* 8MHz internal crystal */
#endif

#include <avr/io.h>
#include <util/delay.h>

#define TEST_PIN (1<<PA0)

int main(void)
{
  int delay_time = 500;

  /* Configure pin as output */
  DDRA = TEST_PIN;

  while(1)
  {
    PORTA |= TEST_PIN;
    _delay_ms(delay_time);
    PORTA &= ~TEST_PIN;
    _delay_ms(delay_time);
  }
}
