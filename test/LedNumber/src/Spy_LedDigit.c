#include "Spy_LedDigit.h"
#include "DataTypes.h"
#include <stdlib.h>
#include <assert.h>

static LedDigit_DisplayDigit * deadDrop;
static int8_t numberOfDigits;
static int8_t memoryIndex;


void Spy_LedDigit_Create(int8_t numDigits)
{
  int i;

  numberOfDigits = numDigits;
  memoryIndex = 0;

  deadDrop = calloc(numberOfDigits, sizeof(LedDigit_DisplayDigit));
  for (i = 0; i < numberOfDigits; i++)
  {
    deadDrop[i] = NOTHING;
  }
}

void Spy_LedDigit_Destroy(void)
{
  memoryIndex = 0;
  free(deadDrop);
}

LedDigit_DisplayDigit LedDigitSpy_GetDigit(int8_t ledNumber)
{
  assert (ledNumber <= numberOfDigits);
  return deadDrop[ledNumber-1];
}


//Spy's re-implementation of LedDigit functions
LedDigit LedDigit_Create(void)
{
  assert (memoryIndex < numberOfDigits);
  return (LedDigit)&deadDrop[memoryIndex++];
}

void LedDigit_Destroy(LedDigit * self)
{

}

void LedDigit_WirePin(LedDigit self, LedDigit_PinNumber pinNumber, int8_t * pinAddress)
{}

void LedDigit_ShowDigit(LedDigit self, LedDigit_DisplayDigit number)
{
  //Due to the way we've wired LedDigit_Create, self points to the dead drop
  LedDigit_DisplayDigit * ptrCast = (LedDigit_DisplayDigit *)self;
  *ptrCast = number;
}

void LedDigit_ShowDecimal(LedDigit self)
{}

void LedDigit_Clear(LedDigit self)
{}
