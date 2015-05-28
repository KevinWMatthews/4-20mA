#ifndef LedNumber_H_
#define LedNumber_H_

#include "LedDigit.h"
#include "DataTypes.h"

typedef struct LedNumberStruct * LedNumber;

typedef enum
{
  //LED1 is the smallest digit
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3,
} LedNumber_DigitPlace;

LedNumber LedNumber_Create(int8_t numberOfDigits);
void LedNumber_AddLedDigit(LedNumber self, LedDigit digit, LedNumber_DigitPlace place);
void LedNumber_Destroy(LedNumber * self);
void LedNumber_SetNumber(LedNumber self, int16_t number);

#endif
