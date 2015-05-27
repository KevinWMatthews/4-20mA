#include "Spy_LedDigit.h"
#include "DataTypes.h"
#include <stdlib.h>


LedDigit LedDigit_Create(LedDigit_DataPins * dataPinAddresses, PinAddress selectPin)
{
  Spy_LedDigit self = calloc(1, sizeof(Spy_LedDigit));
  *self = NOTHING;
  return (LedDigit)self;
}

void LedDigit_Destroy(LedDigit * self)
{
  CHECK_NULL(self);
  free(*self);
}

void LedDigit_ShowDigit(LedDigit self, LedDigit_DisplayDigit number)
{
  CHECK_NULL(self);
  Spy_LedDigit ptrCast = (Spy_LedDigit)self;
  *ptrCast = number;
}

void LedDigit_ShowDecimal(LedDigit self)
{}

LedDigit_DisplayDigit LedDigit_CurrentDigit(LedDigit self)
{
  return NOTHING;
}

void LedDigit_ClearDigit(LedDigit self)
{}

void LedDigit_ClearDecimal(LedDigit self)
{}

void LedDigit_ClearAll(LedDigit self)
{}
