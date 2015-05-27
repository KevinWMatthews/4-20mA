#include "Spy_LedDigit.h"
#include "DataTypes.h"
#include <stdlib.h>
#include <assert.h>

static LedDigit_DisplayDigit * virtualDigits;
static int8_t numberOfDigits;

static int8_t virtualDigitIndex;

void Spy_LedDigit_Create(int8_t numberOfSpyDigits)
{
  numberOfDigits = numberOfSpyDigits;
  virtualDigits = calloc(numberOfDigits, sizeof(LedDigit_DisplayDigit));
  virtualDigitIndex = 0;
}

void Spy_LedDigit_Destroy(void)
{
  numberOfDigits = 0;
  free(virtualDigits);
  virtualDigitIndex = 0;
}

LedDigit_DisplayDigit Spy_LedDigit_GetDigit(int8_t ledNumber)
{
  return virtualDigits[ledNumber-1];
}



LedDigit LedDigit_Create(LedDigit_DataPins * dataPins)
{
  assert (virtualDigitIndex < numberOfDigits);
  return (LedDigit)(&virtualDigits[virtualDigitIndex++]);
}

void LedDigit_Destroy(LedDigit * self)
{
  return;
}

void LedDigit_ShowDigit(LedDigit self, LedDigit_DisplayDigit number)
{
  CHECK_NULL(self);
  LedDigit_DisplayDigit * ptrCast = (LedDigit_DisplayDigit *)self;
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
