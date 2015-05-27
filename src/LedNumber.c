#include "LedNumber.h"
#include "LedDigit.h"
#include <stdlib.h>


typedef struct LedNumberStruct
{
  LedDigit * ledDigits;  //Pointer to a dynamically allocated array of LEDs
  int8_t numberOfDigits;
} LedNumberStruct;


LedNumber LedNumber_Create(LedDigit_DataPins * dataPinAddresses, int8_t numberOfDigits)
{
  LedNumber self = NULL;
  int i;

  self = calloc(1, sizeof(LedNumberStruct));
  self->numberOfDigits = numberOfDigits;
  self->ledDigits = calloc(self->numberOfDigits, sizeof(LedDigit));
  for (i = 0; i < self->numberOfDigits; i++)
  {
    self->ledDigits[i] = LedDigit_Create(dataPinAddresses);
  }
  return self;
}

void LedNumber_Destroy(LedNumber * self)
{
  LedNumber pointer;
  int i;

  CHECK_NULL(self);
  CHECK_NULL(*self);

  pointer = *self;

  for (i = 0; i < pointer->numberOfDigits; i++)
  {
    LedDigit_Destroy(&pointer->ledDigits[i]);
  }
  free(pointer->ledDigits);
  free(pointer);
  self = NULL;
}

void LedNumber_Show(LedNumber self, int16_t number)
{
  LedDigit_ShowDigit(self->ledDigits[0], number);
}
