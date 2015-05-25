#include "LedNumber.h"
#include "LedDigit.h"
#include <stdlib.h>

static PinAddress * ledSelectPins;
static LedDigit * ledDigits;

void LedNumber_Create(int8_t numberOfDigits)
{
  int i;
  ledSelectPins = calloc(numberOfDigits, sizeof(PinAddress));
  ledDigits = calloc(numberOfDigits, sizeof(LedDigit));

  for (i = 0; i < numberOfDigits; i++)
  {
    ledSelectPins[i] = PIN_OFF;
  }
}

void LedNumber_WireSelectPin(int8_t ledNumber, PinAddress memoryAddress)
{
  ledSelectPins[ledNumber-1] = memoryAddress;
}

void LedNumber_Destroy(void)
{
  free(ledSelectPins);
  free(ledDigits);
}

void LedNumber_ShowNumber(int8_t ledNumber, int16_t number)
{
  LedDigit_ShowDigit(ledDigits[0], number);
  *(ledSelectPins[ledNumber-1]) = PIN_ON;
}
