#include "LedNumber.h"
#include "LedDigit.h"
#include <stdlib.h>

#include <assert.h>

//*** Data types ***//
typedef struct LedNumberStruct
{
  LedDigit * ledDigits;       //Pointer to a dynamically allocated array of LEDs
  int8_t numberOfDigits;
} LedNumberStruct;


//*** File-scope function prototypes ***//
static int16_t getDigitFromNumber(int16_t number, int8_t place, int numberOfDigits);


//*** Public functions ***//
LedNumber LedNumber_Create(int8_t numberOfDigits)
{
  LedNumber self = NULL;
  int i;

  self = calloc(1, sizeof(LedNumberStruct));
  self->numberOfDigits = numberOfDigits;
  self->ledDigits = calloc(self->numberOfDigits, sizeof(LedDigit));
  return self;
}

void LedNumber_AddLedDigit(LedNumber self, LedDigit digit, LedNumber_DigitPlace place)
{
  self->ledDigits[place] = digit;
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
    assert(&pointer->ledDigits[i] != NULL);
    LedDigit_Destroy(&pointer->ledDigits[i]);
  }
  free(pointer->ledDigits);
  free(pointer);
  self = NULL;
}

void LedNumber_SetNumber(LedNumber self, int16_t number)
{
  int16_t digitToShow;
  int i;

  for (i = 0; i < self->numberOfDigits; i++)
  {
    digitToShow = getDigitFromNumber(number, i+1, self->numberOfDigits);
    LedDigit_SetDigit(self->ledDigits[i], digitToShow);
  }
}


//*** File-scope function definitions ***//
//place ranges from 1 to numberOfDigits
static int16_t getDigitFromNumber(int16_t number, int8_t place, int numberOfDigits)
{
  int16_t modulusFactor, divisionFactor;
  int i;

  modulusFactor = 10;
  divisionFactor = 1;
  for (i = 1; i < place; i++)
  {
    modulusFactor *= 10;
    divisionFactor *= 10;
  }
  return number % modulusFactor / divisionFactor;
}
