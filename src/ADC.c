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

int8_t Adc_ReadDataRegister_Low(void)
{
  //Return ADCL
}

int8_t Adc_ReadDataRegister_High(void)
{
  //Return ADCH
}

void Adc_ClearInterruptFlag(void)
{
  //Write a 1 to the ADIF register
}
