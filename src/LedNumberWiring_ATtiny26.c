#include "LedNumberWiring.h"
#include <avr/io.h>
#include "BitManip.h"


//********************************************//
//*** Edit here to change hardware wiring! ***//
//********************************************//
#define WIRINGPIN_LED1 (1<<PB0)
#define WIRINGPIN_LED2 (1<<PB1)
#define WIRINGPIN_LED3 (1<<PB2)
#define WIRINGPIN_LED4 (1<<PB3)

//At the moment only portb pins 3, 4, 5, and 6 are available
void LedNumberWiring_Init(void)
{
  DDRB |= WIRINGPIN_LED1 | WIRINGPIN_LED2 | WIRINGPIN_LED3 | WIRINGPIN_LED4;
  PORTB |= WIRINGPIN_LED1 | WIRINGPIN_LED2 | WIRINGPIN_LED3 | WIRINGPIN_LED4;
}

static uint8_t convertPinToWiringPin(LedNumber_DigitPlace pin)
{
  switch (pin)
  {
  case LED_1:
    return WIRINGPIN_LED1;
  case LED_2:
    return WIRINGPIN_LED2;
  case LED_3:
    return WIRINGPIN_LED3;
  case LED_4:
    return WIRINGPIN_LED4;
  }
}

void LedNumberWring_SetSelectPin(LedNumber_DigitPlace pin)
{
  SBIT(PORTB, WIRINGPIN_LED1);
  SBIT(PORTB, WIRINGPIN_LED2);
  SBIT(PORTB, WIRINGPIN_LED3);
  SBIT(PORTB, WIRINGPIN_LED4);
  if (pin == LED_NONE)
  {
    return;
  }
  CBIT(PORTB, convertPinToWiringPin(pin));
}
