#ifndef LedNumber_H_
#define LedNumber_H_

#include "DataTypes.h"

void LedNumber_Create(int8_t numberOfDigits);
void LedNumber_WireSelectPin(int8_t pinNumber, PinAddress memoryAddress);
void LedNumber_Destroy(void);
void LedNumber_ShowNumber(int8_t ledNumber, int16_t number);

#endif
