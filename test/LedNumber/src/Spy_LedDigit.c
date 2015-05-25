#include "Spy_LedDigit.h"
#include "DataTypes.h"
#include <stdlib.h>


//Spy's dead drop
// static LedDigit_DisplayDigit * ones;


//Spy functions
LedDigit_DisplayDigit LedDigitSpy_GetDigit(void)
{
  return NOTHING;
  // return *ones;
}


//Spy's re-implementation of LedDigit functions
LedDigit LedDigit_Create(void)
{
  //Return a dummy pointer that we'll hijack with our spy
  // ones = calloc(1, sizeof(int8_t));
  // return (LedDigit)ones;
  return NULL;
}

void LedDigit_Destroy(LedDigit * self)
{
  // CHECK_NULL(self);
  // free(*self);
  // *self = NULL;
}

void LedDigit_WirePin(LedDigit self, LedDigit_PinNumber pinNumber, int8_t * pinAddress)
{}

void LedDigit_ShowDigit(LedDigit self, LedDigit_DisplayDigit number)
{
  // *ones = number;
}

void LedDigit_ShowDecimal(LedDigit self)
{}

void LedDigit_Clear(LedDigit self)
{}
