#include "LedDigit.h"
#include "DataTypes.h"
#include <stdlib.h>

typedef struct LedDigitPinStruct * LedDigitPins;

//*** File-scope data structures and types ***//
typedef struct LedDigitStruct
{
  LedDigit_DataPins * dataPins;
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
static void setPinState(int8_t * dataPin, Pin state);
static void showNothing(LedDigit_DataPins * pins);
static void showOne(LedDigit_DataPins * pins);
static void showTwo(LedDigit_DataPins * pins);
static void showThree(LedDigit_DataPins * pins);
static void showFour(LedDigit_DataPins * pins);
static void showFive(LedDigit_DataPins * pins);
static void showSix(LedDigit_DataPins * pins);
static void showSeven(LedDigit_DataPins * pins);
static void showEight(LedDigit_DataPins * pins);
static void showNine(LedDigit_DataPins * pins);


//*** Public functions ***//
LedDigit LedDigit_Create(LedDigit_DataPins * dataPinAddresses)
{
  LedDigit self;
  CHECK_NULL_RETURN_VALUE(dataPinAddresses, NULL);
  self = calloc(1, sizeof(LedDigitStruct));
  self->dataPins = dataPinAddresses;
  return self;
}

void LedDigit_Destroy(LedDigit * self)
{
  CHECK_NULL(self);
  free(*self);
  *self = NULL;
}

void LedDigit_ShowDigit(LedDigit self, LedDigit_DisplayDigit number)
{
  CHECK_NULL(self);
  switch (number)
  {
  case NOTHING:
    showNothing(self->dataPins);
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
}

void LedDigit_ShowDecimal(LedDigit self)
{
  CHECK_NULL(self);
  setPinState(self->dataPins->PIN_DP, PIN_ON);
}

void LedDigit_ClearDigit(LedDigit self)
{
  CHECK_NULL(self);
  setPinState(self->dataPins->PIN_A, PIN_OFF);
  setPinState(self->dataPins->PIN_B, PIN_OFF);
  setPinState(self->dataPins->PIN_C, PIN_OFF);
  setPinState(self->dataPins->PIN_D, PIN_OFF);
  setPinState(self->dataPins->PIN_E, PIN_OFF);
  setPinState(self->dataPins->PIN_F, PIN_OFF);
  setPinState(self->dataPins->PIN_G, PIN_OFF);
}

void LedDigit_ClearDecimal(LedDigit self)
{
  CHECK_NULL(self);
  setPinState(self->dataPins->PIN_DP, PIN_OFF);
}

void LedDigit_ClearAll(LedDigit self)
{
  CHECK_NULL(self);
  showNothing(self->dataPins);
}


//*** Private functions ***//
static void setPinState(int8_t * dataPin, Pin state)
{
  CHECK_NULL(dataPin);
  *(dataPin) = state;
}

static void showNothing(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_OFF);
  setPinState(pins->PIN_B, PIN_OFF);
  setPinState(pins->PIN_C, PIN_OFF);
  setPinState(pins->PIN_D, PIN_OFF);
  setPinState(pins->PIN_E, PIN_OFF);
  setPinState(pins->PIN_F, PIN_OFF);
  setPinState(pins->PIN_G, PIN_OFF);
  setPinState(pins->PIN_DP, PIN_OFF);
}

static void showOne(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
}

static void showTwo(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
  setPinState(pins->PIN_E, PIN_ON);
  setPinState(pins->PIN_D, PIN_ON);
}

static void showThree(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
}

static void showFour(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_F, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
}

static void showFive(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_F, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_D, PIN_ON);
}

static void showSix(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_F, PIN_ON);
  setPinState(pins->PIN_E, PIN_ON);
  setPinState(pins->PIN_D, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
}

static void showSeven(LedDigit_DataPins * pins)
{
  setPinState(pins->PIN_A, PIN_ON);
  setPinState(pins->PIN_B, PIN_ON);
  setPinState(pins->PIN_C, PIN_ON);
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
  setPinState(pins->PIN_F, PIN_ON);
  setPinState(pins->PIN_G, PIN_ON);
}
