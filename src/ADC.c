#include "ADC.h"

BOOL Adc_IsAdcBusy(void)
{
  //Read and return the ADSC register
}

void Adc_StartConversion(void)
{
  //Set the ADSC register
}

BOOL Adc_IsInterruptFlagSet(void)
{
  //Read and return the ADIF register
}

int16_t Adc_ReadDataRegisters(void)
{
  //Read ADCL
  //Read ADCH
  //Bit shift result, return as 16-bit variable.
}

void Adc_ClearInterruptFlag(void)
{
  //Write a 1 to the ADIF register
}
