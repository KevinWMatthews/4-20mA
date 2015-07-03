#include "LedNumber.h"
#include "LedNumberWiring.h"
#include "LedDigit.h"
#include <stdlib.h>


#define NO_DIGIT -1


//******************//
//*** Data types ***//
//******************//
typedef struct LedNumberStruct
{
  LedDigit ledDigit;
  LedDigit_DisplayDigit * digits;
  LedNumber_Place largestDigit;
  LedNumber_Place visibleDigit;
} LedNumberStruct;



//**************************************//
//*** File-scope function prototypes ***//
//**************************************//
static LedDigit_DisplayDigit getDigitFromNumber(int16_t number, LedNumber_Place place);
static BOOL isInvalidDigit(LedNumber_Place place);
static int8_t getDigitIndexFromPlace(LedNumber self, LedNumber_Place place);



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
  int8_t i;
  LedNumber self = NULL;

  self = calloc(1, sizeof(LedNumberStruct));
  self->ledDigit = LedDigit_Create();
  self->digits = calloc(largestDigit+1, sizeof(LedDigit_DisplayDigit));
  //TODO use memset or something
  for (i = LED_UNITS; i <= largestDigit; i++)
  {
    self->digits[i] = NOTHING;
  }
  self->largestDigit = largestDigit;
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

  LedDigit_Destroy(&pointer->ledDigit);
  free(pointer->digits);
  free(pointer);
  self = NULL;
}

void LedNumber_SetNumber(LedNumber self, int16_t number)
{
  LedNumber_Place place;
  int8_t index;

  RETURN_IF_NULL(self);
  //MAX_LED check? we've only wired up so many...
  for (place = LED_UNITS; place <= self->largestDigit; place++)
  {
    // index = getDigitIndexFromPlace(self, place);
    self->digits[place] = getDigitFromNumber(number, place);
  }
}

void LedNumber_ClearNumber(LedNumber self)
{
  LedNumber_Place place;

  RETURN_IF_NULL(self);
  for (place = 0; place <= self->largestDigit; place++)
  {
    self->digits[place] = NO_DIGIT;
  }
}

void LedNumber_ShowNumber(LedNumber self)
{
  LedNumber_Place currentDigit;

  RETURN_IF_NULL(self);
  if (isInvalidDigit(self->visibleDigit))  // Wraparound or first time turned on
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


// void LedNumber_TurnOff(LedNumber self)
// {
//   RETURN_IF_NULL(self);
//   LedNumberWiring_SetSelectPin(LED_NONE);
//   self->visibleDigit = LED_NONE;
// }

//*************************//
//*** Private Functions ***//
//*************************//
//This exists purely so I have a way to test it.
LedDigit_DisplayDigit LedDigitPrivate_GetDigitFromNumber(int16_t number, LedNumber_Place place)
{
  return getDigitFromNumber(number, place);
}


//****************************//
//*** File-scope Functions ***//
//****************************//
static LedDigit_DisplayDigit getDigitFromNumber(int16_t number, LedNumber_Place place)
{
  int16_t modulusFactor, divisionFactor;
  LedNumber_Place i;

  modulusFactor = 10;
  divisionFactor = 1;
  for (i = LED_UNITS; i < place; i++)
  {
    modulusFactor *= 10;
    divisionFactor *= 10;
  }
  return (LedDigit_DisplayDigit)(number % modulusFactor / divisionFactor);
}

static BOOL isInvalidDigit(LedNumber_Place place)
{
  return place <= LED_NONE || place >= LED_UPPER_BOUND;
}

//To make for easier viewing in a debugger, digits are stored as such:
// Value:  |units| tens|hundreds|thousands|
// Index:  | [0] | [1] |  [2]   |   [3]   |
static int8_t getDigitIndexFromPlace(LedNumber self, LedNumber_Place place)
{
  return self->largestDigit - place;
}
