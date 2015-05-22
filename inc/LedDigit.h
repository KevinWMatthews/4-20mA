#ifndef LedDigit_H_
#define LedDigit_H_

#include <stdlib.h>

typedef struct LedDigitStruct * LedDigit;
typedef struct LedDigitPinStruct * LedDigitPins;

LedDigit LedDigit_Create(void);
void LedDigit_Destroy(LedDigit * self);

#endif
