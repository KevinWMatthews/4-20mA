#include "DataTypes.h"

void setPinState(PinAddress pin, Pin state)
{
  CHECK_NULL(pin);
  *pin = state;
}
