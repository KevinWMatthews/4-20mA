#include <avr/io.h>

#include "Adc.h"
#include "BitManip.h"

static uint8_t * adcsrPtr;
static uint8_t * admuxPtr;
static uint8_t * adchPtr;
static uint8_t * adclPtr;


//**************************//
//*** Standard Functions ***//
//**************************//
BOOL Adc_IsAdcBusy(void)
{
  RETURN_IF_NULL_RETURN_VALUE(adcsrPtr, FALSE);
  return IFBIT(*adcsrPtr, ADSC);
}

void Adc_StartConversion(void)
{
  RETURN_IF_NULL(adcsrPtr);
  *adcsrPtr = 1 << ADSC;
}

BOOL Adc_IsInterruptFlagSet(void)
{
  RETURN_IF_NULL_RETURN_VALUE(adcsrPtr, FALSE);
  return IFBIT(*adcsrPtr, ADIF);
}

uint8_t Adc_ReadDataRegister_High(void)
{
  //HW only puts values in the lowest two bits of the high register
  RETURN_IF_NULL_RETURN_VALUE(adchPtr, 0);
  return (*adchPtr & 0b11);
}

uint8_t Adc_ReadDataRegister_Low(void)
{
  RETURN_IF_NULL_RETURN_VALUE(adclPtr, 0);
  return *adclPtr;
}

void Adc_ClearInterruptFlag(void)
{
  RETURN_IF_NULL(adcsrPtr);
  *adcsrPtr = 1 << ADIF;
}


//***********************//
//*** Setup functions ***//
//***********************//
void Adc_MapMemory(uint8_t * adcsr, uint8_t * admux, uint8_t * adch, uint8_t * adcl)
{
  adcsrPtr = adcsr;
  admuxPtr = admux;
  adchPtr = adch;
  adclPtr = adcl;
}

void Adc_Init(void)
{
  Adc_Private_SelectReferenceVoltage(ADC_AVCC);
  Adc_Private_SelectResultAdjust(ADC_RIGHT_ADJUST);
  Adc_Private_SelectInputAndGain(ADC_SINGLE_ENDED_ADC0);
  Adc_Private_SelectPrescaleFactor(ADC_PRESCALE_FACTOR_2);
}

void Adc_Private_SelectReferenceVoltage(Adc_VoltageSource voltageSource)
{
  RETURN_IF_NULL(admuxPtr);
  *admuxPtr &= ~(0x03 << REFS0);
  *admuxPtr |= (voltageSource & 0x03) << REFS0;
}

void Adc_Private_SelectResultAdjust(Adc_ResultAdjust resultAdjust)
{
  RETURN_IF_NULL(admuxPtr);
  *admuxPtr &= ~(0x01 << ADLAR);
  *admuxPtr |= (resultAdjust & 0x01) << ADLAR;
}

void Adc_Private_SelectInputAndGain(Adc_AnalogInputAndGain inputAndGain)
{
  RETURN_IF_NULL(admuxPtr);
  *admuxPtr &= ~(0x1f << MUX0);
  *admuxPtr |= (inputAndGain & 0x1f) << MUX0;
}

void Adc_Private_SelectPrescaleFactor(Adc_PrescaleFactor prescaleFactor)
{
  RETURN_IF_NULL(adcsrPtr);
  *adcsrPtr &= ~(0x07 << ADPS0);
  *adcsrPtr |= (prescaleFactor & 0x07) << ADPS0;
}

void Adc_Enable(void)
{
  RETURN_IF_NULL(adcsrPtr);
  *adcsrPtr = ADC_ENABLED << ADEN;
}

void Adc_FirstConversion(void)
{
  RETURN_IF_NULL(adcsrPtr);
  *adcsrPtr = 1 << ADSC;
}
