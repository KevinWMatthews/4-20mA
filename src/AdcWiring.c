#include "AdcWiring.h"
#include <avr/io.h>
#include "BitManip.h"


//**************************//
//*** Standard Functions ***//
//**************************//
BOOL AdcWiring_IsAdcBusy(void)
{
  return IFBIT(ADCSR, ADSC);
}

void AdcWiring_StartConversion(void)
{
  SBI(ADCSR, ADSC);
}

BOOL AdcWiring_IsInterruptFlagSet(void)
{
  return IFBIT(ADCSR, ADIF);
}

uint8_t AdcWiring_ReadDataRegister_High(void)
{
  //HW only puts values in the lowest two bits of the high register
  return (ADCH & 0b11);
}

uint8_t AdcWiring_ReadDataRegister_Low(void)
{
  return ADCL;
}

void AdcWiring_ClearInterruptFlag(void)
{
  SBI(ADCSR, ADIF);
}


//***********************//
//*** Setup functions ***//
//***********************//
void AdcWiring_Init(void)
{
  AdcWiring_Private_SelectReferenceVoltage(ADC_INTERNAL_NO_PA3);
  AdcWiring_Private_SelectResultAdjust(ADC_RIGHT_ADJUST);
  AdcWiring_Private_SelectInputAndGain(ADC_SINGLE_ENDED_ADC0);
  AdcWiring_Private_SelectPrescaleFactor(ADC_PRESCALE_FACTOR_2);
}

void AdcWiring_Private_SelectReferenceVoltage(Adc_VoltageSource voltageSource)
{
  ADMUX &= ~(0x03 << REFS0);
  ADMUX |= (voltageSource & 0x03) << REFS0;
}

void AdcWiring_Private_SelectResultAdjust(Adc_ResultAdjust resultAdjust)
{
  ADMUX &= ~(0x01 << ADLAR);
  ADMUX |= (resultAdjust & 0x01) << ADLAR;
}

void AdcWiring_Private_SelectInputAndGain(Adc_AnalogInputAndGain inputAndGain)
{
  ADMUX &= ~(0x1f << MUX0);
  ADMUX |= (inputAndGain & 0x1f) << MUX0;
}

void AdcWiring_Private_SelectPrescaleFactor(Adc_PrescaleFactor prescaleFactor)
{
  ADCSR &= ~(0x07 << ADPS0);
  ADCSR |= (prescaleFactor & 0x07) << ADPS0;
}

void AdcWiring_Enable(void)
{
  SBI(ADCSR, ADEN);
}

void AdcWiring_FirstConversion(void)
{
  SBI(ADCSR, ADSC);
}
