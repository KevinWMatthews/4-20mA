#include "Spy_LedDigit.h"
#include "DataTypes.h"
#include <stdlib.h>

//*** Spy data structures and functions ***//
typedef struct Spy_LedDigitStruct
{
  LedDigit_DisplayDigit digitOnLed;
  Pin selectPinState;
} Spy_LedDigitStruct;

LedDigit_DisplayDigit Spy_LedDigit_CurrentDigit(Spy_LedDigit self)
{
  CHECK_NULL(self);
  return self->digitOnLed;
}

Pin Spy_LedDigit_SelectPinState(Spy_LedDigit self)
{
  CHECK_NULL(self);
  return self->selectPinState;
}


//*** Spy's mocks of LedDigit functions ***//
LedDigit LedDigit_Create(LedDigit_DataPins * dataPinAddresses, PinAddress selectPin)
{
  Spy_LedDigit self = calloc(1, sizeof(Spy_LedDigitStruct));
  self->digitOnLed = NOTHING;
  self->selectPinState = PIN_OFF;
  return (LedDigit)self;
}

void LedDigit_Destroy(LedDigit * self)
{
  CHECK_NULL(self);
  free(*self);
}

void LedDigit_SetDigit(LedDigit self, LedDigit_DisplayDigit value)
{
  CHECK_NULL(self);
  Spy_LedDigit ptrCast = (Spy_LedDigit)self;
  ptrCast->digitOnLed = value;
}

void LedDigit_SetDecimal(LedDigit self)
{}

void LedDigit_ClearDigit(LedDigit self)
{}

void LedDigit_ClearDecimal(LedDigit self)
{}

void LedDigit_ClearAll(LedDigit self)
{}


LedDigit_DisplayDigit LedDigit_CurrentDigit(LedDigit self)
{
  return NOTHING;
}

BOOL LedDigit_IsDecimalShown(LedDigit self)
{
  return FALSE;
}

void LedDigit_UpdateLed(LedDigit self)
{}

void LedDigit_TurnLedOff(LedDigit self)
{}
