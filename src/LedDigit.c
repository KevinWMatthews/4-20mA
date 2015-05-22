#include "LedDigit.h"
#include "DataTypes.h"
#include <stdlib.h>

typedef struct LedDigitPinStruct * LedDigitPins;

//*** File-scope data structures and types ***//
typedef struct LedDigitStruct
{
  int8_t * pins[PIN_MAX];
} LedDigitStruct;

//The user manual denotes sections of the LED with letters
//and maps these letters to HW pins. We follow suit.
typedef enum
{
  A = PIN7,
  B = PIN6,
  C = PIN4,
  D = PIN2,
  E = PIN1,
  F = PIN9,
  G = PIN10,
  DP = PIN5,
  LETTER_MAX = PIN_MAX
} LedDigit_LetterCode;


//*** Prototypes for file-scope functions ***//
static void setPinState(LedDigit self, LedDigit_LetterCode letter, PinState state);
static void showOne(LedDigit self);
static void showTwo(LedDigit self);
static void showThree(LedDigit self);
static void showFour(LedDigit self);
static void showFive(LedDigit self);
static void showSix(LedDigit self);
static void showSeven(LedDigit self);
static void showEight(LedDigit self);
static void showNine(LedDigit self);


//*** Public functions ***//
LedDigit LedDigit_Create(void)
{
  LedDigit self = calloc(1, sizeof(LedDigitStruct));
  return self;
}

void LedDigit_Destroy(LedDigit * self)
{
  CHECK_NULL(self);
  free(*self);
  *self = NULL;
}

void LedDigit_WirePin(LedDigit self, LedDigit_PinNumber pinNumber, int8_t * pinAddress)
{
  CHECK_NULL(self);
  self->pins[pinNumber] = pinAddress;
}

void LedDigit_ShowDigit(LedDigit self, LedDigit_DisplayDigit number)
{
  CHECK_NULL(self);
  switch (number)
  {
  case NOTHING:
    LedDigit_Clear(self);
    break;
  case ONE:
    showOne(self);
    break;
  case TWO:
    showTwo(self);
    break;
  case THREE:
    showThree(self);
    break;
  case FOUR:
    showFour(self);
    break;
  case FIVE:
    showFive(self);
    break;
  case SIX:
    showSix(self);
    break;
  case SEVEN:
    showSeven(self);
    break;
  case EIGHT:
    showEight(self);
    break;
  case NINE:
    showNine(self);
    break;
  }
}

void LedDigit_ShowDecimal(LedDigit self)
{
  CHECK_NULL(self);
  setPinState(self, DP, PIN_ON);
}

void LedDigit_Clear(LedDigit self)
{
  int8_t i;

  CHECK_NULL(self);
  for (i = 0; i < LETTER_MAX; i++)
  {
    setPinState(self, i, 0);
  }
}


//*** Private functions ***//
static void setPinState(LedDigit self, LedDigit_LetterCode letter, PinState state)
{
  CHECK_NULL(self->pins[letter]);
  *(self->pins[letter]) = state;
}

static void showOne(LedDigit self)
{
  setPinState(self, B, PIN_ON);
  setPinState(self, C, PIN_ON);
}

static void showTwo(LedDigit self)
{
  setPinState(self, A, PIN_ON);
  setPinState(self, B, PIN_ON);
  setPinState(self, G, PIN_ON);
  setPinState(self, E, PIN_ON);
  setPinState(self, D, PIN_ON);
}

static void showThree(LedDigit self)
{
  setPinState(self, A, PIN_ON);
  setPinState(self, B, PIN_ON);
  setPinState(self, C, PIN_ON);
  setPinState(self, D, PIN_ON);
  setPinState(self, G, PIN_ON);
}

static void showFour(LedDigit self)
{
  setPinState(self, F, PIN_ON);
  setPinState(self, G, PIN_ON);
  setPinState(self, B, PIN_ON);
  setPinState(self, C, PIN_ON);
}

static void showFive(LedDigit self)
{
  setPinState(self, A, PIN_ON);
  setPinState(self, F, PIN_ON);
  setPinState(self, G, PIN_ON);
  setPinState(self, C, PIN_ON);
  setPinState(self, D, PIN_ON);
}

static void showSix(LedDigit self)
{
  setPinState(self, A, PIN_ON);
  setPinState(self, F, PIN_ON);
  setPinState(self, E, PIN_ON);
  setPinState(self, D, PIN_ON);
  setPinState(self, C, PIN_ON);
  setPinState(self, G, PIN_ON);
}

static void showSeven(LedDigit self)
{
  setPinState(self, A, PIN_ON);
  setPinState(self, B, PIN_ON);
  setPinState(self, C, PIN_ON);
}

static void showEight(LedDigit self)
{
  setPinState(self, A, PIN_ON);
  setPinState(self, B, PIN_ON);
  setPinState(self, C, PIN_ON);
  setPinState(self, D, PIN_ON);
  setPinState(self, E, PIN_ON);
  setPinState(self, F, PIN_ON);
  setPinState(self, G, PIN_ON);
}

static void showNine(LedDigit self)
{
  setPinState(self, A, PIN_ON);
  setPinState(self, B, PIN_ON);
  setPinState(self, C, PIN_ON);
  setPinState(self, F, PIN_ON);
  setPinState(self, G, PIN_ON);
}
