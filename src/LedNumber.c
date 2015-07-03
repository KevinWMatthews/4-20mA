#include "LedNumber.h"
#include "LedNumberWiring.h"
#include "LedDigit.h"
#include <stdlib.h>



//******************//
//*** Data types ***//
//******************//
typedef struct LedNumberStruct
{
  LedDigit ledDigit;
  LedNumberWiring_Place * selectPins;
  LedNumber_Place largestDigit;
  LedNumber_Place visibleDigit;
} LedNumberStruct;



//**************************************//
//*** File-scope function prototypes ***//
//**************************************//
// int16_t getDigitFromNumber(int16_t number, int8_t place, LedNumber_Place numberSize);
static BOOL isInvalidDigit(LedNumber_Place place);
static int8_t getDigitIndexFromPlace(LedNumber self, LedNumber_Place place);



//************************//
//*** Public Functions ***//
//************************//
void LedNumber_HwSetup(void)
{
  LedNumberWiring_Init();
}

LedNumber LedNumber_Create(LedNumber_Place largestDigit)
{
  LedNumber self = NULL;

  self = calloc(1, sizeof(LedNumberStruct));
  self->ledDigit = LedDigit_Create();
  self->selectPins = calloc(largestDigit+1, sizeof(LedNumberWiring_Place));
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
  free(pointer->selectPins);
  free(pointer);
  self = NULL;
}

// void LedNumber_SetNumber(LedNumber self, int16_t number)
// {
//   int16_t digitToShow;
//   LedNumber_Place place;

//   RETURN_IF_NULL(self);
//   for (place = LED_UNITS; place <= self->largestDigit; place++)
//   {
//     int8_t index = getDigitIndexFromPlace(self, place);
//     RETURN_IF_NULL(self->ledDigits[index]);
//     digitToShow = getDigitFromNumber(number, place);
//     LedDigit_SetDigit(self->ledDigits[index], digitToShow);
//   }
// }

// void LedNumber_ClearNumber(LedNumber self)
// {
//   int i;

//   RETURN_IF_NULL(self);
//   for (i = 0; i <= self->largestDigit; i++)
//   {
//     LedDigit_ClearDigit(self->ledDigits[i]);
//   }
// }

// void LedNumber_ShowNumber(LedNumber self)
// {
//   int8_t index;
//   RETURN_IF_NULL(self);

//   if (isInvalidDigit(self->visibleDigit))  // Wraparound or first time turned on
//   {
//     self->visibleDigit = LED_UNITS;
//   }

//   // switch (self->visibleDigit)
//   // {
//   //   case LED_NONE:
//     //   self->visibleDigit = LED_UNITS;
//     //   LedNumberWiring_SetSelectPin((LedNumberWiring_Place)(LED_UNITS));
//     //   LedDigit_UpdateLed(self->ledDigits[LED_UNITS]);
//     //   break;
//     // case LED_UNITS:
//       // self->visibleDigit = LED_TENS;
//       // LedNumberWiring_SetSelectPin((LedNumberWiring_Place)(LED_TENS));
//       // LedDigit_UpdateLed(self->ledDigits[LED_TENS]);
//       // break;
//     // case LED_TENS:
//     //   self->visibleDigit = LED_HUNDREDS;
//     //   LedNumberWiring_SetSelectPin((LedNumberWiring_Place)(LED_HUNDREDS));
//     //   LedDigit_UpdateLed(self->ledDigits[LED_HUNDREDS]);
//     //   break;
//     // case LED_HUNDREDS:
//     //   self->visibleDigit = LED_THOUSANDS;
//     //   LedNumberWiring_SetSelectPin((LedNumberWiring_Place)(LED_THOUSANDS));
//     //   LedDigit_UpdateLed(self->ledDigits[LED_THOUSANDS]);
//     //   break;
//     // case LED_THOUSANDS:
//     //   self->visibleDigit = LED_UNITS;
//     //   LedNumberWiring_SetSelectPin((LedNumberWiring_Place)(LED_UNITS));
//     //   LedDigit_UpdateLed(self->ledDigits[LED_UNITS]);
//     //   break;
//     // case LED_UPPER_BOUND:
//     //   self->visibleDigit = LED_UNITS;
//     //   LedNumberWiring_SetSelectPin((LedNumberWiring_Place)(LED_UNITS));
//     //   LedDigit_UpdateLed(self->ledDigits[LED_UNITS]);
//     //   break;
//   // }



//   index = getDigitIndexFromPlace(self, self->visibleDigit);
//   // Turn off to prevent "on time" from bleeding to other digit segments
//   LedDigit_TurnLedOff(self->ledDigits[index]);
//   LedNumberWiring_SetSelectPin((LedNumberWiring_Place)(self->visibleDigit));
//   LedDigit_UpdateLed(self->ledDigits[index]);

//   self->visibleDigit++;
// }

// void LedNumber_TurnOff(LedNumber self)
// {
//   RETURN_IF_NULL(self);
//   LedNumberWiring_SetSelectPin(LED_NONE);
//   self->visibleDigit = LED_NONE;
// }



//****************************//
//*** File-scope Functions ***//
//****************************//
int16_t LedDigitPrivate_GetDigitFromNumber(int16_t number, LedNumber_Place place)
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
  return number % modulusFactor / divisionFactor;
}

// static BOOL isInvalidDigit(LedNumber_Place place)
// {
//   return place <= LED_NONE || place >= LED_UPPER_BOUND;
// }

// //To make for easier viewing in a debugger, digits are stored as such:
// // Value:  |units| tens|hundreds|thousands|
// // Index:  | [0] | [1] |  [2]   |   [3]   |
// static int8_t getDigitIndexFromPlace(LedNumber self, LedNumber_Place place)
// {
//   return self->largestDigit - place;
// }
