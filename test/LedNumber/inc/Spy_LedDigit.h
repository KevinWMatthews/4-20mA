#ifndef Spy_LedDigit_H_
#define Spy_LedDigit_H_

#include "LedDigit.h"

typedef LedDigit_DisplayDigit * Spy_LedDigit;

void Spy_LedDigit_Create(int8_t numberOfSpyDigits);
void Spy_LedDigit_Destroy(void);
LedDigit_DisplayDigit Spy_LedDigit_GetDigit(int8_t ledNumber);

#endif
