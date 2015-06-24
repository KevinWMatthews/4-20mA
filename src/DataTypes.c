#include "DataTypes.h"
#include <stdlib.h>


//********************//
typedef struct PinStruct
{
  uint8_t * address;
  uint8_t bitmask;
  PinState state;
} PinStruct;

Pin Pin_Create(uint8_t * address, uint8_t bitmask)
{
  Pin self = NULL;

  self = calloc(1, sizeof(PinStruct));
  self->address = address;
  self->bitmask = bitmask;
  self->state = PIN_UNDEFINED;
  return self;
}

void Pin_Destroy(Pin * self)
{
  CHECK_NULL(self);
  CHECK_NULL(*self);
  free(*self);
  *self = NULL;
}

uint8_t * Pin_GetAddress(Pin self)
{
  CHECK_NULL_RETURN_VALUE(self, NULL);
  return self->address;
}

uint8_t Pin_GetBitmask(Pin self)
{
  CHECK_NULL_RETURN_VALUE(self, NULL_POINTER);
  return self->bitmask;
}

PinState Pin_GetState(Pin self)
{
  CHECK_NULL_RETURN_VALUE(self, PIN_NULL_POINTER);
  return self->state;
}


void Pin_SetState(Pin self, PinState state)
{
  CHECK_NULL(self);
  self->state = state;
  if (state == PIN_HIGH)
  {
    *(self->address) |= self->bitmask;  //SBI
  }
  else if (state == PIN_LOW)
  {
    *(self->address) &= ~(self->bitmask); //CBI
  }
}
