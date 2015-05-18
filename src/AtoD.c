#include "AtoD.h"
#include "ADC.h"

int8_t AtoD_StartConversion(void)
{
  if (Adc_IsAdcBusy())
  {
    return ATOD_BUSY;
  }

  Adc_StartConversion();
  return ATOD_CONVERSION_STARTED;
}

int8_t AtoD_Read(int16_t * reading)
{
  if (Adc_IsAdcBusy())
  {
    return ATOD_BUSY;
  }
  if (!Adc_IsInterruptFlagSet())
  {
    return ATOD_INTERRUPT_FLAG_NOT_SET;
  }
  *reading = Adc_ReadDataRegisters();
  Adc_ClearInterruptFlag();
  return ATOD_READ_SUCCESS;
}
