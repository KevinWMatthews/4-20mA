#include "LedDigit.h"
#include <stdlib.h>
#include "DataTypes.h"

typedef struct LedDigitStruct
{
  int8_t current_digit;
} LedDigitStruct;

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
