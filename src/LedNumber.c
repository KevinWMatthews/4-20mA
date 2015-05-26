#include "LedNumber.h"
#include "LedDigit.h"
#include <stdlib.h>


static LedDigit * ledDigits;
static int8_t numberOfDigits;


void LedNumber_Create(int8_t numDigits)
{
  int i;
  numberOfDigits = numDigits;
  ledDigits = calloc(numberOfDigits, sizeof(LedDigit));

  for (i = 0; i < numberOfDigits; i++)
  {
    ledDigits[i] = LedDigit_Create();
  }
}


void LedNumber_Destroy(void)
{
  int i;
  for (i = 0; i < numberOfDigits; i++)
  {
    LedDigit_Destroy(&ledDigits[i]);
  }
  free(ledDigits);
}

//Digits run from 1 to numberOfDigits
static LedDigit_DisplayDigit extractDigit(int16_t number, uint8_t digit)
{
  int16_t modulusFactor, divisionFactor;
  int i;

  if (digit < 1)
  {
    return NOTHING;
  }

  modulusFactor = 10;
  divisionFactor = 1;
  for (i = 1; i < digit; i++)
  {
    modulusFactor *= 10;
    divisionFactor *= 10;
  }
  return number % modulusFactor / divisionFactor;
}

void LedNumber_ShowNumber(int16_t number)
{
  int i;
  for (i = 0; i < numberOfDigits; i++)
  {
    LedDigit_ShowDigit(ledDigits[i], extractDigit(number, i+1));
  }
}
