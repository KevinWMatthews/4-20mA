#ifndef LedNumber_H_
#define LedNumber_H_

#include <stdint.h>

void LedNumber_Create(int8_t * ledSelectPin);
void LedNumber_Destroy(void);
void LedNumber_ShowNumber(int16_t number);

#endif
