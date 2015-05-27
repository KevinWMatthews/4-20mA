#ifndef LedNumber_H_
#define LedNumber_H_

#include "LedDigit.h"
#include "DataTypes.h"

void LedNumber_Create(LedDigit_DataPins * dataPinAddresses, int8_t numberOfDigits);
void LedNumber_Destroy(void);

#endif
