#include "LedNumber.h"
#include "LedDigit.h"
#include <stdlib.h>

#include <assert.h>

//*** Data types ***//
typedef struct LedNumberStruct
{
  LedDigit * ledDigits;       //Pointer to a dynamically allocated array of LEDs
  int8_t numberOfDigits;
  LedNumber_DigitPlace visibleDigit;
} LedNumberStruct;


//*** File-scope function prototypes ***//
static int16_t getDigitFromNumber(int16_t number, int8_t place, int numberOfDigits);
static BOOL isValidDigit(LedNumber_DigitPlace place);


//*** Public functions ***//
LedNumber LedNumber_Create(int8_t numberOfDigits)
{
  LedNumber self = NULL;

  self = calloc(1, sizeof(LedNumberStruct));
  self->numberOfDigits = numberOfDigits;
  self->ledDigits = calloc(self->numberOfDigits, sizeof(LedDigit));
  self->visibleDigit = NO_LED;
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

  // CHECK_NULL(self);
  for (i = 0; i < self->numberOfDigits; i++)
  {
    digitToShow = getDigitFromNumber(number, i+1, self->numberOfDigits);
    LedDigit_SetDigit(self->ledDigits[i], digitToShow);
  }
}

void LedNumber_ClearNumber(LedNumber self)
{
  int i;

  // CHECK_NULL(self);

  for (i = 0; i < self->numberOfDigits; i++)
  {
    LedDigit_ClearDigit(self->ledDigits[i]);
  }
}

void LedNumber_ShowNumber(LedNumber self)
{
  // CHECK_NULL(self);

  if (isValidDigit(self->visibleDigit))
  {
    LedDigit_TurnLedOff(self->ledDigits[self->visibleDigit]);
    self->visibleDigit--;
  }

  if (!isValidDigit(self->visibleDigit))  // Wraparound or first time turned on
  {
    self->visibleDigit = LED_MAX - 1;
  }

  LedDigit_UpdateLed(self->ledDigits[self->visibleDigit]);
}

void LedNumber_TurnOff(LedNumber self)
{
  // CHECK_NULL(self);
  LedDigit_TurnLedOff(self->ledDigits[self->visibleDigit]);
  self->visibleDigit = NO_LED;
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

static BOOL isValidDigit(LedNumber_DigitPlace place)
{
  return place != NO_LED && place != LED_MAX;
}
