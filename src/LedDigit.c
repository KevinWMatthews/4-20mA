#include "LedDigit.h"
#include "DataTypes.h"

typedef struct LedDigitPinStruct
{
  int8_t * pins[10];
} LedDigitPinStruct;

typedef struct LedDigitStruct
{
  LedDigitPins pinWiring;
} LedDigitStruct;


LedDigit LedDigit_Create(void)
{
  LedDigit self = calloc(1, sizeof(LedDigitStruct));
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
