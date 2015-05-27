#include "LedNumber.h"
#include "LedDigit.h"
#include <stdlib.h>

typedef struct LedNumberStruct
{
  LedDigit * ledDigits;       //Pointer to a dynamically allocated array of LEDs
  PinAddress * ledSelectPins; //Pointer to a dynamically allocated array of Pins
  int8_t numberOfDigits;
} LedNumberStruct;


LedNumber LedNumber_Create(int8_t numberOfDigits)
{
  LedNumber self = NULL;
  int i;

  self = calloc(1, sizeof(LedNumberStruct));
  self->numberOfDigits = numberOfDigits;
  self->ledDigits = calloc(self->numberOfDigits, sizeof(LedDigit));
  self->ledSelectPins = calloc(self->numberOfDigits, sizeof(PinAddress));
  return self;
}

void LedNumber_AddLedDigit(LedNumber self, LedDigit digit, LedNumber_DigitPlace place, PinAddress selectPin)
{
  self->ledDigits[place] = digit;
  self->ledSelectPins[place] = selectPin;
  *(self->ledSelectPins[place]) = PIN_OFF;
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
  free(pointer->ledSelectPins);
  free(pointer);
  self = NULL;
}

void LedNumber_Show(LedNumber self, int16_t number)
{
  LedDigit_ShowDigit(self->ledDigits[0], number);
  *(self->ledSelectPins[0]) = PIN_ON;
}
