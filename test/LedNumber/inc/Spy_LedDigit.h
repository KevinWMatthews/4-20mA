#ifndef Spy_LedDigit_H_
#define Spy_LedDigit_H_

#include "LedDigit.h"

//Create the spy BEFORE creating LedNumber!
void Spy_LedDigit_Create(int8_t numDigits);
void Spy_LedDigit_Destroy(void);
LedDigit_DisplayDigit LedDigitSpy_GetDigit(int8_t ledNumber);

#endif
