#include "LedDigit.h"
#include "DataTypes.h"

typedef struct LedDigitPinStruct
{
  int8_t * pins[10];
} LedDigitPinStruct;

typedef struct LedDigitStruct
{
  LedDigit_Digit current_digit;
  LedDigitPins pinWiring;
} LedDigitStruct;

void LedDigit_WirePins(LedDigit self, int8_t pinNumber, int8_t * pinAddress)
{
  self->pinWiring->pins[pinNumber-1] = pinAddress;
}

LedDigit LedDigit_Create(void)
{
  LedDigit self = calloc(1, sizeof(LedDigitStruct));
  self->current_digit = LED_DIGIT_NO_DIGIT;
  self->pinWiring = calloc(1, sizeof(LedDigitPinStruct));
  return self;
}

void LedDigit_Destroy(LedDigit * self)
{
  CHECK_NULL(self);
  CHECK_NULL(*self);
  free((*self)->pinWiring);
  free(*self);
  *self = NULL;
}

void LedDigit_Clear(LedDigit self)
{

}

LedDigit_Digit LedDigit_CurrentDigit(LedDigit self)
{
  return self->current_digit;
}

void display8(LedDigitPins pinWiring)
{
  //Must handle null pointer
  //Nasty; want to set pins either by number but prefereably by letter?
  *(pinWiring->pins[0]) = 1;
  *(pinWiring->pins[1]) = 1;
  *(pinWiring->pins[3]) = 1;
  *(pinWiring->pins[4]) = 1;
  *(pinWiring->pins[5]) = 1;
  *(pinWiring->pins[6]) = 1;
  *(pinWiring->pins[8]) = 1;
  *(pinWiring->pins[9]) = 1;
  //set pin A
  //set pin B
  //set pin C
  //set pin D
  //set pin E
  //set pin F
  //set pin G
}

void LedDigit_SetDigit(LedDigit self, LedDigit_Digit value)
{
  switch (value)
  {
    case LED_DIGIT_8:
      display8(self->pinWiring);
      break;
  }
  self->current_digit = value;
}
