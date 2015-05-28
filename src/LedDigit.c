#include "LedDigit.h"
#include "DataTypes.h"
#include <stdlib.h>

typedef struct LedDigitPinStruct * LedDigitPins;

//*** File-scope data structures and types ***//
typedef struct LedDigitStruct
{
  LedDigit_DataPins * dataPins;
  PinAddress selectPin;
  LedDigit_DisplayDigit digitToShow;
  BOOL showDecimal;
} LedDigitStruct;

//The user manual denotes sections of the LED with letters
//and maps these letters to HW pins. We follow suit.
#define PIN_A pin7
#define PIN_B pin6
#define PIN_C pin4
#define PIN_D pin2
#define PIN_E pin1
#define PIN_F pin9
#define PIN_G pin10
#define PIN_DP pin5


//*** Prototypes for file-scope functions ***//
static void showNothing(LedDigit_DataPins * pins);
static void showZero(LedDigit_DataPins * pins);
static void showOne(LedDigit_DataPins * pins);
static void showTwo(LedDigit_DataPins * pins);
static void showThree(LedDigit_DataPins * pins);
static void showFour(LedDigit_DataPins * pins);
static void showFive(LedDigit_DataPins * pins);
static void showSix(LedDigit_DataPins * pins);
static void showSeven(LedDigit_DataPins * pins);
static void showEight(LedDigit_DataPins * pins);
static void showNine(LedDigit_DataPins * pins);
static void showDecimal(LedDigit_DataPins * pins);
static void clearDecimal(LedDigit_DataPins * pins);


//*** Public functions ***//
LedDigit LedDigit_Create(LedDigit_DataPins * dataPinAddresses, PinAddress selectPin)
{
  LedDigit self;
  CHECK_NULL_RETURN_VALUE(dataPinAddresses, NULL);
  CHECK_NULL_RETURN_VALUE(selectPin, NULL);

  self = calloc(1, sizeof(LedDigitStruct));
  self->dataPins = dataPinAddresses;
  self->selectPin = selectPin;

  showNothing(self->dataPins);
  *(self->selectPin) = PIN_OFF;
  self->digitToShow = NOTHING;
  self->showDecimal = FALSE;

  return self;
}

void LedDigit_Destroy(LedDigit * self)
{
  CHECK_NULL(self);
  free(*self);
  *self = NULL;
}

void LedDigit_SetDigit(LedDigit self, LedDigit_DisplayDigit value)
{
  CHECK_NULL(self);
  self->digitToShow = value;
}

void LedDigit_SetDecimal(LedDigit self)
{
  CHECK_NULL(self);
  self->showDecimal = TRUE;
}

void LedDigit_ClearDigit(LedDigit self)
{
  CHECK_NULL(self);
  self->digitToShow = NOTHING;
}

void LedDigit_ClearDecimal(LedDigit self)
{
  CHECK_NULL(self);
  self->showDecimal = FALSE;
}

void LedDigit_ClearAll(LedDigit self)
{
  CHECK_NULL(self);
  LedDigit_ClearDigit(self);
  LedDigit_ClearDecimal(self);
}

LedDigit_DisplayDigit LedDigit_CurrentDigit(LedDigit self)
{
  CHECK_NULL(self);
  return self->digitToShow;
}

BOOL LedDigit_IsDecimalShown(LedDigit self)
{
  CHECK_NULL(self);
  return self->showDecimal;
}

void LedDigit_UpdateLed(LedDigit self)
{
  CHECK_NULL(self);

  switch (self->digitToShow)
  {
  case NOTHING:
    showNothing(self->dataPins);
    break;
  case ZERO:
    showZero(self->dataPins);
    break;
  case ONE:
    showOne(self->dataPins);
    break;
  case TWO:
    showTwo(self->dataPins);
    break;
  case THREE:
    showThree(self->dataPins);
    break;
  case FOUR:
    showFour(self->dataPins);
    break;
  case FIVE:
    showFive(self->dataPins);
    break;
  case SIX:
    showSix(self->dataPins);
    break;
  case SEVEN:
    showSeven(self->dataPins);
    break;
  case EIGHT:
    showEight(self->dataPins);
    break;
  case NINE:
    showNine(self->dataPins);
    break;
  }

  if (self->showDecimal == TRUE)
  {
    showDecimal(self->dataPins);
  }
  else
  {
    clearDecimal(self->dataPins);
  }

  setPinState(self->selectPin, PIN_ON);
}

void LedDigit_TurnLedOff(LedDigit self)
{
  CHECK_NULL(self);
  setPinState(self->selectPin, PIN_OFF);
  showNothing(self->dataPins);
  clearDecimal(self->dataPins);
}


//*** Private functions ***//
static void showNothing(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_OFF);
  setPinState(pins->PIN_B, PIN_OFF);
  setPinState(pins->PIN_C, PIN_OFF);
  setPinState(pins->PIN_D, PIN_OFF);
  setPinState(pins->PIN_E, PIN_OFF);
  setPinState(pins->PIN_F, PIN_OFF);
  setPinState(pins->PIN_G, PIN_OFF);
}

static void showZero(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_ON);
  setPinState(pins->PIN_E, PIN_ON);
  setPinState(pins->PIN_F, PIN_ON);
  setPinState(pins->PIN_G, PIN_OFF);
}

static void showOne(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_OFF);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_OFF);
  setPinState(pins->PIN_E, PIN_OFF);
  setPinState(pins->PIN_F, PIN_OFF);
  setPinState(pins->PIN_G, PIN_OFF);
}

static void showTwo(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_OFF);
  setPinState(pins->PIN_D, PIN_ON);
  setPinState(pins->PIN_E, PIN_ON);
  setPinState(pins->PIN_F, PIN_OFF);
  setPinState(pins->PIN_G, PIN_ON);
}

static void showThree(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_ON);
  setPinState(pins->PIN_E, PIN_OFF);
  setPinState(pins->PIN_F, PIN_OFF);
  setPinState(pins->PIN_G, PIN_ON);
}

static void showFour(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_OFF);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_OFF);
  setPinState(pins->PIN_E, PIN_OFF);
  setPinState(pins->PIN_F, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
}

static void showFive(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_OFF);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_ON);
  setPinState(pins->PIN_E, PIN_OFF);
  setPinState(pins->PIN_F, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
}

static void showSix(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_OFF);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_ON);
  setPinState(pins->PIN_E, PIN_ON);
  setPinState(pins->PIN_F, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
}

static void showSeven(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_OFF);
  setPinState(pins->PIN_E, PIN_OFF);
  setPinState(pins->PIN_F, PIN_OFF);
  setPinState(pins->PIN_G, PIN_OFF);
}

static void showEight(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_ON);
  setPinState(pins->PIN_E, PIN_ON);
  setPinState(pins->PIN_F, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
}

static void showNine(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_OFF);
  setPinState(pins->PIN_E, PIN_OFF);
  setPinState(pins->PIN_F, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
}

static void showDecimal(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_DP, PIN_ON);
}

static void clearDecimal(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_DP, PIN_OFF);
}
