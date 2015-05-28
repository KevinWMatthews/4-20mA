#ifndef LedNumber_H_
#define LedNumber_H_

#include "LedDigit.h"
#include "DataTypes.h"

typedef struct LedNumberStruct * LedNumber;

typedef enum
{
  //LED1 is the smallest digit
  NO_LED = -1,
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3,
  LED_MAX = 4
} LedNumber_DigitPlace;

LedNumber LedNumber_Create(int8_t numberOfDigits);
void LedNumber_AddLedDigit(LedNumber self, LedDigit digit, LedNumber_DigitPlace place);
void LedNumber_Destroy(LedNumber * self);

void LedNumber_SetNumber(LedNumber self, int16_t number);
void LedNumber_ClearNumber(LedNumber self);

void LedNumber_ShowNumber(LedNumber self);
void LedNumber_TurnOff(LedNumber self);

#endif
