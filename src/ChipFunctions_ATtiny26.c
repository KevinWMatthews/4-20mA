#include "ChipFunctions.h"
#include "BitManip.h"
#include <avr/interrupt.h>

void ChipFunctions_EnableGlobalInterrupts(void)
{
  //This call is specific to AVR chips
  //Can also manually set bit 7 (I) of SREG
  sei();
}

void ChipFunctions_DisableGlobalInterrupts(void)
{
  //This call is specific to AVR chips
  //Can also manually clear bit 7 (I) of SREG
  cli();
}
