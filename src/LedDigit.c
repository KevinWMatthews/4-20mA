#include "LedDigit.h"
#include "DataTypes.h"

typedef struct LedDigitStruct
{
  LedDigit_Digit current_digit;
} LedDigitStruct;

LedDigit LedDigit_Create(void)
{
  LedDigit self = calloc(1, sizeof(LedDigitStruct));
  self->current_digit = LED_DIGIT_NO_DIGIT;
  return self;
}

void LedDigit_Destroy(LedDigit * self)
{
  CHECK_NULL(self);
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

void LedDigit_SetDigit(LedDigit self, LedDigit_Digit value)
{
  self->current_digit = value;
}
