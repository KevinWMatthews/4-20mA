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

typedef struct
{
  PinAddress pin1;
  PinAddress pin2;
  PinAddress pin4;
  PinAddress pin5;
  PinAddress pin6;
  PinAddress pin7;
  PinAddress pin9;
  PinAddress pin10;
} LedDigit_DataPins;

LedDigit LedDigit_Create(LedDigit_DataPins * dataPinAddresses, PinAddress selectPin);
void LedDigit_Destroy(LedDigit * self);
void LedDigit_SetDigit(LedDigit self, LedDigit_DisplayDigit value);
void LedDigit_SetDecimal(LedDigit self);
void LedDigit_ShowDigit(LedDigit self);
void LedDigit_ShowDecimal(LedDigit self);
LedDigit_DisplayDigit LedDigit_CurrentValue(LedDigit self);
BOOL LedDigit_IsDecimalShown(LedDigit self);
void LedDigit_ClearDigit(LedDigit self);
void LedDigit_ClearDecimal(LedDigit self);
void LedDigit_ClearAll(LedDigit self);

#endif
