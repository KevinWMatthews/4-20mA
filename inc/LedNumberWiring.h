#ifndef LedNumberWiring_H_
#define LedNumberWiring_H_

#define LED_MAX 4

typedef enum
{
  //LED_1 is the smallest digit
  LED_NONE = -1,
  LED_1 = 0,
  LED_2 = 1,
  LED_3 = 2,
  LED_4 = 3
} LedNumber_DigitPlace;

void LedNumberWiring_Init(void);

//Pin selection is mutually exclusive - only one pin will be selected at a time.
//Selecting any new pin unselects all others.
void LedNumberWring_SetSelectPin(LedNumber_DigitPlace pin);

#endif
