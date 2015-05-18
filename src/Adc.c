#include "Adc.h"

static uint8_t * adcsrPtr;

void Adc_Init(uint8_t * adcsr)
{
  adcsrPtr = adcsr;
}

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

//Setup functions
void Adc_SelectReferenceVoltage(Adc_VoltageSource voltageSource)
{
  *adcsrPtr = voltageSource << REFS0;
}

void Adc_SelectResultAdjust(Adc_ResultAdjust resultAdjust)
{
  //Set ADLAR
}

void Adc_SelectInputAndGain(Adc_AnalogInputAndGain inputAndGain)
{
  //Set MUX4..0
}

void Adc_SetPrescaleFactor(Adc_PrescaleFactor prescaleFactor)
{
  //Set ADPS2..0
}

void Adc_Enable(void)
{
  //Set ADEN
}

void Adc_FirstConversion(void)
{
  //Set ADSC
}
