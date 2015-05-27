#ifndef LedNumber_H_
#define LedNumber_H_

#include "LedDigit.h"
#include "DataTypes.h"

typedef struct LedNumberStruct * LedNumber;

LedNumber LedNumber_Create(LedDigit_DataPins * dataPinAddresses, int8_t numberOfDigits);
void LedNumber_Destroy(LedNumber * self);
void LedNumber_Show(LedNumber self, int16_t number);

#endif
