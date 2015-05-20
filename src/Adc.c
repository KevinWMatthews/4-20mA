#include <avr/io.h>

#include "Adc.h"
#include "BitManip.h"

static uint8_t * adcsrPtr;
static uint8_t * admuxPtr;
static uint8_t * adchPtr;
static uint8_t * adclPtr;

void Adc_Init(uint8_t * adcsr, uint8_t * admux, uint8_t * adch, uint8_t * adcl)
{
  adcsrPtr = adcsr;
  admuxPtr = admux;
  adchPtr = adch;
  adclPtr = adcl;
}

BOOL Adc_IsAdcBusy(void)
{
  return IFBIT(*adcsrPtr, ADSC);
}

void Adc_StartConversion(void)
{
  *adcsrPtr = 1 << ADSC;
}

BOOL Adc_IsInterruptFlagSet(void)
{
  return IFBIT(*adcsrPtr, ADIF);
}

uint8_t Adc_ReadDataRegister_High(void)
{
  //HW only puts values in the lowest two bits of the high register
  return (*adchPtr & 0b11);
}

uint8_t Adc_ReadDataRegister_Low(void)
{
  return *adclPtr;
}

void Adc_ClearInterruptFlag(void)
{
  *adcsrPtr = 1 << ADIF;
}

//Setup functions
void Adc_SelectReferenceVoltage(Adc_VoltageSource voltageSource)
{
  *admuxPtr = voltageSource << REFS0;
}

void Adc_SelectResultAdjust(Adc_ResultAdjust resultAdjust)
{
  *admuxPtr = resultAdjust << ADLAR;
}

void Adc_SelectInputAndGain(Adc_AnalogInputAndGain inputAndGain)
{
  *admuxPtr = inputAndGain << MUX0;
}

void Adc_SetPrescaleFactor(Adc_PrescaleFactor prescaleFactor)
{
  *adcsrPtr = prescaleFactor << ADPS0;
}

void Adc_Enable(void)
{
  *adcsrPtr = ADC_ENABLED << ADEN;
}

void Adc_FirstConversion(void)
{
  *adcsrPtr = 1 << ADSC;
}
