#include "Adc.h"
#include <avr/io.h>
#include "BitManip.h"


//**************************//
//*** Standard Functions ***//
//**************************//
BOOL Adc_IsAdcBusy(void)
{
  return IFBIT(ADCSR, ADSC);
}

void Adc_StartConversion(void)
{
  ADCSR = 1 << ADSC;
}

BOOL Adc_IsInterruptFlagSet(void)
{
  return IFBIT(ADCSR, ADIF);
}

uint8_t Adc_ReadDataRegister_High(void)
{
  //HW only puts values in the lowest two bits of the high register
  return (ADCH & 0b11);
}

uint8_t Adc_ReadDataRegister_Low(void)
{
  return ADCL;
}

void Adc_ClearInterruptFlag(void)
{
  ADCSR = 1 << ADIF;
}


//***********************//
//*** Setup functions ***//
//***********************//
void Adc_Init(void)
{
  Adc_Private_SelectReferenceVoltage(ADC_AVCC);
  Adc_Private_SelectResultAdjust(ADC_RIGHT_ADJUST);
  Adc_Private_SelectInputAndGain(ADC_SINGLE_ENDED_ADC0);
  Adc_Private_SelectPrescaleFactor(ADC_PRESCALE_FACTOR_2);
}

void Adc_Private_SelectReferenceVoltage(Adc_VoltageSource voltageSource)
{
  ADMUX &= ~(0x03 << REFS0);
  ADMUX |= (voltageSource & 0x03) << REFS0;
}

void Adc_Private_SelectResultAdjust(Adc_ResultAdjust resultAdjust)
{
  ADMUX &= ~(0x01 << ADLAR);
  ADMUX |= (resultAdjust & 0x01) << ADLAR;
}

void Adc_Private_SelectInputAndGain(Adc_AnalogInputAndGain inputAndGain)
{
  ADMUX &= ~(0x1f << MUX0);
  ADMUX |= (inputAndGain & 0x1f) << MUX0;
}

void Adc_Private_SelectPrescaleFactor(Adc_PrescaleFactor prescaleFactor)
{
  ADCSR &= ~(0x07 << ADPS0);
  ADCSR |= (prescaleFactor & 0x07) << ADPS0;
}

void Adc_Enable(void)
{
  ADCSR = ADC_ENABLED << ADEN;
}

void Adc_FirstConversion(void)
{
  ADCSR = 1 << ADSC;
}
