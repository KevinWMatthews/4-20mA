#include "DataTypes.h"
#include <stdlib.h>


void setPinState(PinAddress pin, Pin state)
{
  CHECK_NULL(pin);
  *pin = state;
}

//********************//
typedef struct _PinStruct
{
  int8_t * address;
  int8_t bitmask;
  _PinState state;
} _PinStruct;

_Pin Pin_Create(int8_t * address, int8_t bitmask)
{
  _Pin self = NULL;

  self = calloc(1, sizeof(_PinStruct));
  self->address = address;
  self->bitmask = bitmask;
  self->state = _PIN_UNDEFINED;
  return self;
}

void Pin_Destroy(_Pin * self)
{
  CHECK_NULL(self);
  CHECK_NULL(*self);
  free(*self);
  *self = NULL;
}

int8_t * Pin_GetAddress(_Pin self)
{
  CHECK_NULL_RETURN_VALUE(self, NULL);
  return self->address;
}

int8_t Pin_GetBitmask(_Pin self)
{
  CHECK_NULL_RETURN_VALUE(self, NULL_POINTER);
  return self->bitmask;
}

_PinState Pin_GetState(_Pin self)
{
  CHECK_NULL_RETURN_VALUE(self, _PIN_NULL_POINTER);
  return self->state;
}


void Pin_SetState(_Pin self, _PinState state)
{
  CHECK_NULL(self);
  self->state = state;
}
