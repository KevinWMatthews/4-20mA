#ifndef LedDigit_H_
#define LedDigit_H_

#include "DataTypes.h"
#include <stdint.h>

typedef struct LedDigitStruct * LedDigit;

typedef enum
{
  NOTHING = -1,
  ZERO = 0,
  ONE = 1,
  TWO = 2,
  THREE = 3,
  FOUR = 4,
  FIVE = 5,
  SIX = 6,
  SEVEN = 7,
  EIGHT = 8,
  NINE = 9
} LedDigit_DisplayDigit;


LedDigit LedDigit_Create(void);
void LedDigit_Destroy(LedDigit * self);

void LedDigit_SetDigit(LedDigit self, LedDigit_DisplayDigit value);
void LedDigit_SetDecimal(LedDigit self);
void LedDigit_ClearDigit(LedDigit self);
void LedDigit_ClearDecimal(LedDigit self);
void LedDigit_ClearAll(LedDigit self);
LedDigit_DisplayDigit LedDigit_CurrentDigit(LedDigit self);
BOOL LedDigit_IsDecimalShown(LedDigit self);

void LedDigit_UpdateLed(LedDigit self);
void LedDigit_TurnLedOff(LedDigit self);

#endif
