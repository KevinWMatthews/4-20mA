#include "LedDigit.h"
#include "LedDigitWiring.h"
#include "DataTypes.h"
#include <stdlib.h>


//*** File-scope data structures and types ***//
typedef struct LedDigitStruct
{
  LedDigit_DisplayDigit digitToShow;
  BOOL showDecimal;
} LedDigitStruct;

//The user manual denotes sections of the LED with letters
//and maps these letters to HW pins. We follow suit.
// #define PIN_A pin7
// #define PIN_B pin6
// #define PIN_C pin4
// #define PIN_D pin2
// #define PIN_E pin1
// #define PIN_F pin9
// #define PIN_G pin10
// #define PIN_DP pin5


//*** Prototypes for file-scope functions ***//
static void showNothing(void);
static void showZero(void);
static void showOne(void);
static void showTwo(void);
static void showThree(void);
static void showFour(void);
static void showFive(void);
static void showSix(void);
static void showSeven(void);
static void showEight(void);
static void showNine(void);
static void showDecimal(void);
static void clearDecimal(void);


//*** Public functions ***//
LedDigit LedDigit_Create(void)
{
  LedDigit self;

  self = calloc(1, sizeof(LedDigitStruct));

  showNothing();
  clearDecimal();
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
  CHECK_NULL_RETURN_VALUE(self, NOTHING);
  return self->digitToShow;
}

BOOL LedDigit_IsDecimalShown(LedDigit self)
{
  CHECK_NULL_RETURN_VALUE(self, FALSE);
  return self->showDecimal;
}

void LedDigit_UpdateLed(LedDigit self)
{
  CHECK_NULL(self);

  switch (self->digitToShow)
  {
  case NOTHING:
    showNothing();
    break;
  case ZERO:
    showZero();
    break;
  case ONE:
    showOne();
    break;
  case TWO:
    showTwo();
    break;
  case THREE:
    showThree();
    break;
  case FOUR:
    showFour();
    break;
  case FIVE:
    showFive();
    break;
  case SIX:
    showSix();
    break;
  case SEVEN:
    showSeven();
    break;
  case EIGHT:
    showEight();
    break;
  case NINE:
    showNine();
    break;
  }

  if (self->showDecimal == TRUE)
  {
    showDecimal();
  }
  else
  {
    clearDecimal();
  }
}

void LedDigit_TurnLedOff(LedDigit self)
{
  CHECK_NULL(self);
  showNothing();
  clearDecimal();
}


//*** Private functions ***//
static void showNothing(void)
{
  LedDigitWiring_ClearPin(PIN_A);
  LedDigitWiring_ClearPin(PIN_B);
  LedDigitWiring_ClearPin(PIN_C);
  LedDigitWiring_ClearPin(PIN_D);
  LedDigitWiring_ClearPin(PIN_E);
  LedDigitWiring_ClearPin(PIN_F);
  LedDigitWiring_ClearPin(PIN_G);
}

static void showZero(void)
{
  LedDigitWiring_SetPin(PIN_A);
  LedDigitWiring_SetPin(PIN_B);
  LedDigitWiring_SetPin(PIN_C);
  LedDigitWiring_SetPin(PIN_D);
  LedDigitWiring_SetPin(PIN_E);
  LedDigitWiring_SetPin(PIN_F);
  LedDigitWiring_ClearPin(PIN_G);
}

static void showOne(void)
{
  LedDigitWiring_ClearPin(PIN_A);
  LedDigitWiring_SetPin(PIN_B);
  LedDigitWiring_SetPin(PIN_C);
  LedDigitWiring_ClearPin(PIN_D);
  LedDigitWiring_ClearPin(PIN_E);
  LedDigitWiring_ClearPin(PIN_F);
  LedDigitWiring_ClearPin(PIN_G);
}

static void showTwo(void)
{
  LedDigitWiring_SetPin(PIN_A);
  LedDigitWiring_SetPin(PIN_B);
  LedDigitWiring_ClearPin(PIN_C);
  LedDigitWiring_SetPin(PIN_D);
  LedDigitWiring_SetPin(PIN_E);
  LedDigitWiring_ClearPin(PIN_F);
  LedDigitWiring_SetPin(PIN_G);
}

static void showThree(void)
{
  LedDigitWiring_SetPin(PIN_A);
  LedDigitWiring_SetPin(PIN_B);
  LedDigitWiring_SetPin(PIN_C);
  LedDigitWiring_SetPin(PIN_D);
  LedDigitWiring_ClearPin(PIN_E);
  LedDigitWiring_ClearPin(PIN_F);
  LedDigitWiring_SetPin(PIN_G);
}

static void showFour(void)
{
  LedDigitWiring_ClearPin(PIN_A);
  LedDigitWiring_SetPin(PIN_B);
  LedDigitWiring_SetPin(PIN_C);
  LedDigitWiring_ClearPin(PIN_D);
  LedDigitWiring_ClearPin(PIN_E);
  LedDigitWiring_SetPin(PIN_F);
  LedDigitWiring_SetPin(PIN_G);
}

static void showFive(void)
{
  LedDigitWiring_SetPin(PIN_A);
  LedDigitWiring_ClearPin(PIN_B);
  LedDigitWiring_SetPin(PIN_C);
  LedDigitWiring_SetPin(PIN_D);
  LedDigitWiring_ClearPin(PIN_E);
  LedDigitWiring_SetPin(PIN_F);
  LedDigitWiring_SetPin(PIN_G);
}

static void showSix(void)
{
  LedDigitWiring_SetPin(PIN_A);
  LedDigitWiring_ClearPin(PIN_B);
  LedDigitWiring_SetPin(PIN_C);
  LedDigitWiring_SetPin(PIN_D);
  LedDigitWiring_SetPin(PIN_E);
  LedDigitWiring_SetPin(PIN_F);
  LedDigitWiring_SetPin(PIN_G);
}

static void showSeven(void)
{
  LedDigitWiring_SetPin(PIN_A);
  LedDigitWiring_SetPin(PIN_B);
  LedDigitWiring_SetPin(PIN_C);
  LedDigitWiring_ClearPin(PIN_D);
  LedDigitWiring_ClearPin(PIN_E);
  LedDigitWiring_ClearPin(PIN_F);
  LedDigitWiring_ClearPin(PIN_G);
}

static void showEight(void)
{
  LedDigitWiring_SetPin(PIN_A);
  LedDigitWiring_SetPin(PIN_B);
  LedDigitWiring_SetPin(PIN_C);
  LedDigitWiring_SetPin(PIN_D);
  LedDigitWiring_SetPin(PIN_E);
  LedDigitWiring_SetPin(PIN_F);
  LedDigitWiring_SetPin(PIN_G);
}

static void showNine(void)
{
  LedDigitWiring_SetPin(PIN_A);
  LedDigitWiring_SetPin(PIN_B);
  LedDigitWiring_SetPin(PIN_C);
  LedDigitWiring_ClearPin(PIN_D);
  LedDigitWiring_ClearPin(PIN_E);
  LedDigitWiring_SetPin(PIN_F);
  LedDigitWiring_SetPin(PIN_G);
}

static void showDecimal(void)
{
  LedDigitWiring_SetPin(PIN_DP);
}

static void clearDecimal(void)
{
  LedDigitWiring_ClearPin(PIN_DP);
}
