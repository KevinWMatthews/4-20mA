#ifndef LedDigit_H_
#define LedDigit_H_

typedef struct LedDigitStruct * LedDigit;

LedDigit LedDigit_Create(void);
void LedDigit_Destroy(LedDigit * self);

#endif
