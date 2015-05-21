#ifndef LedDigit_H_
#define LedDigit_H_

#include <stdlib.h>

typedef struct LedDigitStruct * LedDigit;

typedef enum
{
  LED_DIGIT_NO_DIGIT = -1,
  LED_DIGIT_8        = 8
} LedDigit_Digit;

LedDigit LedDigit_Create(void);
void LedDigit_Destroy(LedDigit * self);
void LedDigit_Clear(LedDigit self);
LedDigit_Digit LedDigit_CurrentDigit(LedDigit self);
void LedDigit_SetDigit(LedDigit self, LedDigit_Digit value);

#endif
