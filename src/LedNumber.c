#include "LedNumber.h"
#include "LedNumberWiring.h"
#include "LedDigit.h"
#include <stdlib.h>



//******************//
//*** Data types ***//
//******************//
typedef struct LedNumberStruct
{
  LedDigit * ledDigits;       //Pointer to a dynamically allocated array of LEDs
  int8_t numberOfDigits;
  LedNumber_DigitPlace visibleDigit;
} LedNumberStruct;



//**************************************//
//*** File-scope function prototypes ***//
//**************************************//
static int16_t getDigitFromNumber(int16_t number, int8_t place, int numberOfDigits);
static BOOL isValidDigit(LedNumber_DigitPlace place);



//************************//
//*** Public Functions ***//
//************************//
LedNumber LedNumber_Create(int8_t numberOfDigits)
{
  LedNumber self = NULL;

  self = calloc(1, sizeof(LedNumberStruct));
  self->numberOfDigits = numberOfDigits;
  self->ledDigits = calloc(self->numberOfDigits, sizeof(LedDigit));
  self->visibleDigit = LED_NONE;
  return self;
}

void LedNumber_Destroy(LedNumber * self)
{
  LedNumber pointer;
  int i;

  RETURN_IF_NULL(self);
  RETURN_IF_NULL(*self);

  pointer = *self;

  for (i = 0; i < pointer->numberOfDigits; i++)
  {
    LedDigit_Destroy(&pointer->ledDigits[i]);
  }
  free(pointer->ledDigits);
  free(pointer);
  self = NULL;
}

void LedNumber_AddLedDigit(LedNumber self, LedDigit digit, LedNumber_DigitPlace place)
{
  RETURN_IF_NULL(self);
  self->ledDigits[place] = digit;
}

void LedNumber_SetNumber(LedNumber self, int16_t number)
{
  int16_t digitToShow;
  int i;

  RETURN_IF_NULL(self);
  for (i = 0; i < self->numberOfDigits; i++)
  {
    RETURN_IF_NULL(self->ledDigits[i]);
    digitToShow = getDigitFromNumber(number, i+1, self->numberOfDigits);
    LedDigit_SetDigit(self->ledDigits[i], digitToShow);
  }
}

void LedNumber_ClearNumber(LedNumber self)
{
  int i;

  RETURN_IF_NULL(self);
  for (i = 0; i < self->numberOfDigits; i++)
  {
    LedDigit_ClearDigit(self->ledDigits[i]);
  }
}

void LedNumber_ShowNumber(LedNumber self)
{
  RETURN_IF_NULL(self);

  if (isValidDigit(self->visibleDigit))
  {
    self->visibleDigit--;
  }

  if (!isValidDigit(self->visibleDigit))  // Wraparound or first time turned on
  {
    self->visibleDigit = self->numberOfDigits - 1;
  }
  //Turn off to prevent "on time" from bleeding to other digit segments
  LedDigit_TurnLedOff(self->ledDigits[self->visibleDigit]);
  LedNumberWring_SetSelectPin((LedNumber_DigitPlace)(self->numberOfDigits - self->visibleDigit - 1));
  LedDigit_UpdateLed(self->ledDigits[self->visibleDigit]);
}

void LedNumber_TurnOff(LedNumber self)
{
  RETURN_IF_NULL(self);
  LedNumberWring_SetSelectPin(LED_NONE);
  self->visibleDigit = LED_NONE;
}



//****************************//
//*** File-scope Functions ***//
//****************************//
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
  return place != LED_NONE && place != LED_MAX;
}
