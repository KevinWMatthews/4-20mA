#include "LedNumber.h"
#include "LedNumberWiring.h"
#include "LedDigit.h"
#include <stdlib.h>
#include <string.h>



//******************//
//*** Data types ***//
//******************//
//Digits are stored as such:
// Value:  |units| tens|hundreds|thousands|
// Index:  | [0] | [1] |  [2]   |   [3]   |
typedef struct LedNumberStruct
{
  LedDigit ledDigit;
  LedDigit_Value * digits;
  LedNumber_Place largestDigit;
  LedNumber_Place visibleDigit;
} LedNumberStruct;



//**************************************//
//*** File-scope function prototypes ***//
//**************************************//
static LedDigit_Value getDigitFromNumber(int16_t number, LedNumber_Place place);
static BOOL isDigitOutOfBounds(LedNumber_Place place);
static BOOL isDigitVisible(LedNumber_Place place);
static BOOL isBeyondLargestDigit(LedNumber self);
static BOOL isNumberOutOfRange(LedNumber self, int16_t number);



//************************//
//*** Public Functions ***//
//************************//
void LedNumber_HwSetup(void)
{
  LedDigit_HwSetup();
  LedNumberWiring_HwSetup();
}

LedNumber LedNumber_Create(LedNumber_Place largestDigit)
{
  LedNumber self;
  int8_t i;

  if (isDigitOutOfBounds(largestDigit))
  {
    return NULL;
  }
  self = calloc(1, sizeof(LedNumberStruct));
  RETURN_VALUE_IF_NULL(self, NULL);

  self->ledDigit = LedDigit_Create();
  RETURN_VALUE_IF_NULL(self->ledDigit, NULL);

  self->digits = calloc(largestDigit+1, sizeof(LedDigit_Value));
  RETURN_VALUE_IF_NULL(self->digits, NULL);
  for (i = LED_UNITS; i <= largestDigit; i++)
  {
    self->digits[i] = NO_DIGIT;
  }
  self->largestDigit = largestDigit;
  self->visibleDigit = LED_NONE;
  return self;
}

void LedNumber_Destroy(LedNumber * self)
{
  LedNumber pointer;

  RETURN_IF_NULL(self);
  RETURN_IF_NULL(*self);

  pointer = *self;

  LedDigit_Destroy(&pointer->ledDigit);
  free(pointer->digits);
  free(pointer);
  *self = NULL;
}

void LedNumber_SetNumber(LedNumber self, int16_t number)
{
  LedNumber_Place place;

  RETURN_IF_NULL(self);

  if (isNumberOutOfRange(self, number) == TRUE )
  {
    return;
  }
  for (place = LED_UNITS; place <= self->largestDigit; place++)
  {
    self->digits[place] = getDigitFromNumber(number, place);
  }
}

void LedNumber_ShowNumber(LedNumber self)
{
  LedNumber_Place currentDigit;

  RETURN_IF_NULL(self);

  if (!isDigitVisible(self->visibleDigit))
  {
    self->visibleDigit = LED_UNITS;
  }
  if (isBeyondLargestDigit(self))   //Wraparound
  {
    self->visibleDigit = LED_UNITS;
  }

  currentDigit = self->visibleDigit;

  // Turn off to prevent "on time" from bleeding to other digit segments
  LedDigit_TurnLedOff(self->ledDigit);
  LedNumberWiring_SetSelectPin((LedNumberWiring_Place)(currentDigit));
  LedDigit_SetDigit(self->ledDigit, self->digits[currentDigit]);
  LedDigit_UpdateLed(self->ledDigit);

  self->visibleDigit++;
}



//*************************//
//*** Private Functions ***//
//*************************//
//These exist purely for testing.
LedDigit_Value LedDigitPrivate_GetDigitFromNumber(int16_t number, LedNumber_Place place)
{
  return getDigitFromNumber(number, place);
}



//****************************//
//*** File-scope Functions ***//
//****************************//
static LedDigit_Value getDigitFromNumber(int16_t number, LedNumber_Place place)
{
  int32_t modulusFactor, divisionFactor;
  LedNumber_Place i;

  modulusFactor = 10;
  divisionFactor = 1;
  for (i = LED_UNITS; i < place; i++)
  {
    modulusFactor *= 10;
    divisionFactor *= 10;
  }
  return (LedDigit_Value)(number % modulusFactor / divisionFactor);
}

static BOOL isDigitOutOfBounds(LedNumber_Place place)
{
  return place >= LED_UPPER_BOUND || place <= LED_NONE;
}

static BOOL isDigitVisible(LedNumber_Place place)
{
  return place != LED_NONE;
}

static BOOL isBeyondLargestDigit(LedNumber self)
{
  RETURN_VALUE_IF_NULL(self, TRUE);
  return self->visibleDigit > self->largestDigit;
}

static BOOL isNumberOutOfRange(LedNumber self, int16_t number)
{
  if (number < 0)
  {
    return TRUE;
  }
  return getDigitFromNumber(number, (LedNumber_Place)(self->largestDigit+1)) != 0;
}
