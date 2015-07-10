#include "NumericFunctions.h"



//************************//
//*** Public Functions ***//
//************************//
int16_t round_int16(float value)
{
  if (value >= 0)
  {
    return (int16_t)(value + 0.5);
  }
  else
  {
    return (int16_t)(value - 0.5);
  }
}
