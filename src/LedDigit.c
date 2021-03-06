#include "LedDigit.h"
#include "LedDigitWiring.h"
#include "DataTypes.h"
#include <stdlib.h>



//******************//
//*** Data Types ***//
//******************//
typedef struct LedDigitStruct
{
  LedDigit_Value digitToShow;
  BOOL showDecimal;
} LedDigitStruct;



//*******************************************//
//*** Prototypes for file-scope functions ***//
//*******************************************//
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



//************************//
//*** Public Functions ***//
//************************//
void LedDigit_HwSetup(void)
{
  LedDigitWiring_HwSetup();
}

LedDigit LedDigit_Create(void)
{
  LedDigit self;

  self = calloc(1, sizeof(LedDigitStruct));

  showNothing();
  clearDecimal();
  self->digitToShow = NO_DIGIT;
  self->showDecimal = FALSE;

  return self;
}

void LedDigit_Destroy(LedDigit * self)
{
  RETURN_IF_NULL(self);
  free(*self);
  *self = NULL;
}

void LedDigit_SetDigit(LedDigit self, LedDigit_Value value)
{
  RETURN_IF_NULL(self);
  self->digitToShow = value;
}

void LedDigit_SetDecimal(LedDigit self)
{
  RETURN_IF_NULL(self);
  self->showDecimal = TRUE;
}

void LedDigit_ClearDigit(LedDigit self)
{
  RETURN_IF_NULL(self);
  self->digitToShow = NO_DIGIT;
}

void LedDigit_ClearDecimal(LedDigit self)
{
  RETURN_IF_NULL(self);
  self->showDecimal = FALSE;
}

void LedDigit_ClearAll(LedDigit self)
{
  RETURN_IF_NULL(self);
  LedDigit_ClearDigit(self);
  LedDigit_ClearDecimal(self);
}

LedDigit_Value LedDigit_CurrentDigit(LedDigit self)
{
  RETURN_VALUE_IF_NULL(self, NO_DIGIT);
  return self->digitToShow;
}

BOOL LedDigit_IsDecimalShown(LedDigit self)
{
  RETURN_VALUE_IF_NULL(self, FALSE);
  return self->showDecimal;
}

void LedDigit_UpdateLed(LedDigit self)
{
  RETURN_IF_NULL(self);

  switch (self->digitToShow)
  {
  case NO_DIGIT:
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
  RETURN_IF_NULL(self);
  showNothing();
  clearDecimal();
}



//****************************//
//*** File-scope Functions ***//
//****************************//
static void showNothing(void)
{
  LedDigitWiring_TurnSegmentOff(PIN_A);
  LedDigitWiring_TurnSegmentOff(PIN_B);
  LedDigitWiring_TurnSegmentOff(PIN_C);
  LedDigitWiring_TurnSegmentOff(PIN_D);
  LedDigitWiring_TurnSegmentOff(PIN_E);
  LedDigitWiring_TurnSegmentOff(PIN_F);
  LedDigitWiring_TurnSegmentOff(PIN_G);
}

static void showZero(void)
{
  LedDigitWiring_TurnSegmentOn(PIN_A);
  LedDigitWiring_TurnSegmentOn(PIN_B);
  LedDigitWiring_TurnSegmentOn(PIN_C);
  LedDigitWiring_TurnSegmentOn(PIN_D);
  LedDigitWiring_TurnSegmentOn(PIN_E);
  LedDigitWiring_TurnSegmentOn(PIN_F);
  LedDigitWiring_TurnSegmentOff(PIN_G);
}

static void showOne(void)
{
  LedDigitWiring_TurnSegmentOff(PIN_A);
  LedDigitWiring_TurnSegmentOn(PIN_B);
  LedDigitWiring_TurnSegmentOn(PIN_C);
  LedDigitWiring_TurnSegmentOff(PIN_D);
  LedDigitWiring_TurnSegmentOff(PIN_E);
  LedDigitWiring_TurnSegmentOff(PIN_F);
  LedDigitWiring_TurnSegmentOff(PIN_G);
}

static void showTwo(void)
{
  LedDigitWiring_TurnSegmentOn(PIN_A);
  LedDigitWiring_TurnSegmentOn(PIN_B);
  LedDigitWiring_TurnSegmentOff(PIN_C);
  LedDigitWiring_TurnSegmentOn(PIN_D);
  LedDigitWiring_TurnSegmentOn(PIN_E);
  LedDigitWiring_TurnSegmentOff(PIN_F);
  LedDigitWiring_TurnSegmentOn(PIN_G);
}

static void showThree(void)
{
  LedDigitWiring_TurnSegmentOn(PIN_A);
  LedDigitWiring_TurnSegmentOn(PIN_B);
  LedDigitWiring_TurnSegmentOn(PIN_C);
  LedDigitWiring_TurnSegmentOn(PIN_D);
  LedDigitWiring_TurnSegmentOff(PIN_E);
  LedDigitWiring_TurnSegmentOff(PIN_F);
  LedDigitWiring_TurnSegmentOn(PIN_G);
}

static void showFour(void)
{
  LedDigitWiring_TurnSegmentOff(PIN_A);
  LedDigitWiring_TurnSegmentOn(PIN_B);
  LedDigitWiring_TurnSegmentOn(PIN_C);
  LedDigitWiring_TurnSegmentOff(PIN_D);
  LedDigitWiring_TurnSegmentOff(PIN_E);
  LedDigitWiring_TurnSegmentOn(PIN_F);
  LedDigitWiring_TurnSegmentOn(PIN_G);
}

static void showFive(void)
{
  LedDigitWiring_TurnSegmentOn(PIN_A);
  LedDigitWiring_TurnSegmentOff(PIN_B);
  LedDigitWiring_TurnSegmentOn(PIN_C);
  LedDigitWiring_TurnSegmentOn(PIN_D);
  LedDigitWiring_TurnSegmentOff(PIN_E);
  LedDigitWiring_TurnSegmentOn(PIN_F);
  LedDigitWiring_TurnSegmentOn(PIN_G);
}

static void showSix(void)
{
  LedDigitWiring_TurnSegmentOn(PIN_A);
  LedDigitWiring_TurnSegmentOff(PIN_B);
  LedDigitWiring_TurnSegmentOn(PIN_C);
  LedDigitWiring_TurnSegmentOn(PIN_D);
  LedDigitWiring_TurnSegmentOn(PIN_E);
  LedDigitWiring_TurnSegmentOn(PIN_F);
  LedDigitWiring_TurnSegmentOn(PIN_G);
}

static void showSeven(void)
{
  LedDigitWiring_TurnSegmentOn(PIN_A);
  LedDigitWiring_TurnSegmentOn(PIN_B);
  LedDigitWiring_TurnSegmentOn(PIN_C);
  LedDigitWiring_TurnSegmentOff(PIN_D);
  LedDigitWiring_TurnSegmentOff(PIN_E);
  LedDigitWiring_TurnSegmentOff(PIN_F);
  LedDigitWiring_TurnSegmentOff(PIN_G);
}

static void showEight(void)
{
  LedDigitWiring_TurnSegmentOn(PIN_A);
  LedDigitWiring_TurnSegmentOn(PIN_B);
  LedDigitWiring_TurnSegmentOn(PIN_C);
  LedDigitWiring_TurnSegmentOn(PIN_D);
  LedDigitWiring_TurnSegmentOn(PIN_E);
  LedDigitWiring_TurnSegmentOn(PIN_F);
  LedDigitWiring_TurnSegmentOn(PIN_G);
}

static void showNine(void)
{
  LedDigitWiring_TurnSegmentOn(PIN_A);
  LedDigitWiring_TurnSegmentOn(PIN_B);
  LedDigitWiring_TurnSegmentOn(PIN_C);
  LedDigitWiring_TurnSegmentOff(PIN_D);
  LedDigitWiring_TurnSegmentOff(PIN_E);
  LedDigitWiring_TurnSegmentOn(PIN_F);
  LedDigitWiring_TurnSegmentOn(PIN_G);
}

static void showDecimal(void)
{
  LedDigitWiring_TurnSegmentOn(PIN_DP);
}

static void clearDecimal(void)
{
  LedDigitWiring_TurnSegmentOff(PIN_DP);
}
