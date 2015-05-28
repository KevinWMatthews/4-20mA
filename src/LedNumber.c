#include "LedNumber.h"
#include "LedDigit.h"
#include <stdlib.h>

#include <assert.h>

//*** Data types ***//
typedef struct LedNumberStruct
{
  LedDigit * ledDigits;       //Pointer to a dynamically allocated array of LEDs
  PinAddress * ledSelectPins; //Pointer to a dynamically allocated array of Pins
  int8_t numberOfDigits;
} LedNumberStruct;


//*** File-scope function prototypes ***//
static void setSelectPinState(PinAddress pinPointer, Pin state);
static int16_t getDigitFromNumber(int16_t number, int8_t place, int numberOfDigits);


//*** Public functions ***//
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
    assert(&pointer->ledDigits[i] != NULL);
    LedDigit_Destroy(&pointer->ledDigits[i]);
  }
  free(pointer->ledDigits);
  free(pointer->ledSelectPins);
  free(pointer);
  self = NULL;
}

void LedNumber_Show(LedNumber self, int16_t number)
{
  int16_t digitToShow;
  int i;

  for (i = 0; i < self->numberOfDigits; i++)
  {
    digitToShow = getDigitFromNumber(number, i+1, self->numberOfDigits);
    //TODO add SetDigit
    // LedDigit_ShowDigit(self->ledDigits[i], digitToShow);
    setSelectPinState(self->ledSelectPins[i], PIN_ON);
  }
}


//*** File-scope function definitions ***//
static void setSelectPinState(PinAddress pinPointer, Pin state)
{
  CHECK_NULL(pinPointer);
  *pinPointer = state;
}

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
