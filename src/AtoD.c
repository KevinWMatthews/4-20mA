#include "AtoD.h"
#include "ADC.h"

int8_t AtoD_Read(void)
{
  if (isAdcBusy())
    return ATOD_BUSY;
}
