#include "PinDriver.h"

void PinDriver_SetBit(volatile uint8_t * address, uint8_t bit)
{
  *address |= (1 << bit);
}

void PinDriver_ClearBit(volatile uint8_t * address, uint8_t bit)
{
  *address &= ~(1<<bit);
}

BOOL PinDriver_IfBit(volatile uint8_t * address, uint8_t bit)
{
  return 1 && (*address & (1<<bit));
}
