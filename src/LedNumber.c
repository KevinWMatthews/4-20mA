#include "LedNumber.h"
#include "LedDigit.h"
#include <stdlib.h>


typedef struct LedNumber
{
  LedDigit * ledDigits;  //Pointer to a dynamically allocated array of LEDs
  int8_t numberOfDigits;
} LedNumber;


// Single-instance module, so here's our single instance
static LedNumber ledNumber;


void LedNumber_Create(LedDigit_DataPins * dataPinAddresses, int8_t numberOfDigits)
{
  int i;

  ledNumber.numberOfDigits = numberOfDigits;
  ledNumber.ledDigits = calloc(ledNumber.numberOfDigits, sizeof(LedDigit));
  for (i = 0; i < ledNumber.numberOfDigits; i++)
  {
    ledNumber.ledDigits[i] = LedDigit_Create(dataPinAddresses);
  }
}

void LedNumber_Destroy(void)
{
  int i;

  for (i = 0; i < ledNumber.numberOfDigits; i++)
  {
    LedDigit_Destroy(&ledNumber.ledDigits[i]);
  }
  free(ledNumber.ledDigits);
  ledNumber.numberOfDigits = 0;
}
