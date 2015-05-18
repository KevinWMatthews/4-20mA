#include "AtoD.h"
#include "ADC.h"

int8_t AtoD_StartConversion(void)
{
  if (isAdcBusy())
  {
    return ATOD_BUSY;
  }

  startConversion();
  return ATOD_CONVERSION_STARTED;
}

int8_t AtoD_Read(int16_t * reading)
{
  if (isAdcBusy())
  {
    return ATOD_BUSY;
  }
  if (!isInterruptFlagSet())
  {
    return ATOD_INTERRUPT_FLAG_NOT_SET;
  }
}
