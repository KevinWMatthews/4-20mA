#include "AdcWiring.h"
#include <avr/io.h>
#include "BitManip.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Edit here to change hardware setup! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void AdcWiring_HwSetup(void)
{
  AdcWiring_Private_SelectReferenceVoltage(ADC_AVCC);
  AdcWiring_Private_SelectResultAdjust(ADC_RIGHT_ADJUST);
  AdcWiring_Private_SelectInputAndGain(ADC_SINGLE_ENDED_ADC0);
  AdcWiring_Private_SelectPrescaleFactor(ADC_PRESCALE_FACTOR_2);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~ Hardware setup modification should not cause changes below this point! ~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//



void AdcWiring_Enable(void)
{
  SET_BIT_NUMBER(ADCSR, ADEN);
}

void AdcWiring_FirstConversion(void)
{
  SET_BIT_NUMBER(ADCSR, ADSC);
}

BOOL AdcWiring_IsAdcBusy(void)
{
  return IF_BIT_NUMBER(ADCSR, ADSC);
}

void AdcWiring_StartConversion(void)
{
  SET_BIT_NUMBER(ADCSR, ADSC);
}

BOOL AdcWiring_IsInterruptFlagSet(void)
{
  return IF_BIT_NUMBER(ADCSR, ADIF);
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
  SET_BIT_NUMBER(ADCSR, ADIF);
}



//*************************//
//*** Private Functions ***//
//*************************//
//These functions are in the header file only to facilitate in-depth testing
void AdcWiring_Private_SelectReferenceVoltage(Adc_VoltageSource voltageSource)
{
  SHIFT_AND_SET_BITMASK_TO(ADMUX, voltageSource, ADC_VOLTAGE_SOURCE_BITMASK);
}

void AdcWiring_Private_SelectResultAdjust(Adc_ResultAdjust resultAdjust)
{
  SHIFT_AND_SET_BITMASK_TO(ADMUX, resultAdjust, ADC_RESULT_ADJUST_BITMASK);
}

void AdcWiring_Private_SelectInputAndGain(Adc_AnalogInputAndGain inputAndGain)
{
  SHIFT_AND_SET_BITMASK_TO(ADMUX, inputAndGain, ADC_ANALOG_INPUT_AND_GAIN_BITMASK);
}

void AdcWiring_Private_SelectPrescaleFactor(Adc_PrescaleFactor prescaleFactor)
{
  SHIFT_AND_SET_BITMASK_TO(ADCSR, prescaleFactor, ADC_PRESCALE_FACTOR_BITMASK);
}
