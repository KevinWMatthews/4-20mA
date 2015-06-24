#ifndef PinDriver_H_
#define PinDriver_H_

#include "DataTypes.h"

void PinDriver_SetBit(volatile uint8_t * address, uint8_t bit);
void PinDriver_ClearBit(volatile uint8_t * address, uint8_t bit);
BOOL PinDriver_IfBit(volatile uint8_t * address, uint8_t bit);

#endif
