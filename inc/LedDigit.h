#ifndef LedDigit_H_
#define LedDigit_H_

#include "DataTypes.h"



//******************//
//*** Data Types ***//
//******************//
typedef struct LedDigitStruct * LedDigit;

typedef enum
{
  NO_DIGIT = -1,
  ZERO     = 0,
  ONE      = 1,
  TWO      = 2,
  THREE    = 3,
  FOUR     = 4,
  FIVE     = 5,
  SIX      = 6,
  SEVEN    = 7,
  EIGHT    = 8,
  NINE     = 9
} LedDigit_Value;



//************************//
//*** Public Functions ***//
//************************//
void LedDigit_HwSetup(void);
LedDigit LedDigit_Create(void);
void LedDigit_Destroy(LedDigit * self);

void LedDigit_SetDigit(LedDigit self, LedDigit_Value value);
void LedDigit_SetDecimal(LedDigit self);
void LedDigit_ClearDigit(LedDigit self);
void LedDigit_ClearDecimal(LedDigit self);
void LedDigit_ClearAll(LedDigit self);
LedDigit_Value LedDigit_CurrentDigit(LedDigit self);
BOOL LedDigit_IsDecimalShown(LedDigit self);

void LedDigit_UpdateLed(LedDigit self);
void LedDigit_TurnLedOff(LedDigit self);

#endif
