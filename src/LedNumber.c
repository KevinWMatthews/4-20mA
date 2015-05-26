#include "LedNumber.h"
#include "LedDigit.h"
#include <stdlib.h>


static LedDigit ledDigits[1];


void LedNumber_Create(int8_t numDigits)
{
  // ledDigits = calloc(numDigits, sizeof(LedDigit));
  ledDigits[0] = LedDigit_Create();
}


void LedNumber_Destroy(void)
{
  LedDigit_Destroy(&ledDigits[0]);
}

void LedNumber_ShowNumber(int8_t ledNumber, int16_t number)
{
  LedDigit_ShowDigit(ledDigits[0], number);
}
