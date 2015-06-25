#ifndef LedNumber_H_
#define LedNumber_H_

#include "LedDigit.h"
#include "LedNumberWiring.h"
#include "DataTypes.h"

typedef struct LedNumberStruct * LedNumber;


LedNumber LedNumber_Create(int8_t numberOfDigits);
void LedNumber_AddLedDigit(LedNumber self, LedDigit digit, LedNumber_DigitPlace place);
void LedNumber_Destroy(LedNumber * self);

void LedNumber_SetNumber(LedNumber self, int16_t number);
void LedNumber_ClearNumber(LedNumber self);

void LedNumber_ShowNumber(LedNumber self);
void LedNumber_TurnOff(LedNumber self);

#endif
