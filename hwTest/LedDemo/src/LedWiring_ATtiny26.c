#include "LedWiring.h"
#include "BitManip.h"

void LedWiring_Init(void)
{
  //Configure LED pins as outputs
  DDRA = (LED_1) | LED_2 | LED_3 | LED_4 | LED_5 | LED_6 | LED_7 | LED_8;
}

void LedWiring_SetLed(int8_t ledNumber)
{
  SBIT(PORTA, ledNumber);
}

void LedWiring_ClearLed(int8_t ledNumber)
{
  CBIT(PORTA, ledNumber);
}
