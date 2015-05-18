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
