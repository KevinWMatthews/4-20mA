#include "Spy_LedDigit.h"
#include "DataTypes.h"
#include <stdlib.h>


static LedDigit_DisplayDigit deadDrop;


LedDigit_DisplayDigit LedDigitSpy_GetDigit(int8_t ledNumber)
{
  return deadDrop;
}


//Spy's re-implementation of LedDigit functions
LedDigit LedDigit_Create(void)
{
  return (LedDigit)&deadDrop;
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
