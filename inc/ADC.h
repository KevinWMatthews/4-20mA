#ifndef ADC_H_
#define ADC_H_

#include "DataTypes.h"
#include <stdint.h>

typedef enum
{
  ADC_AVCC = 0b00
} Adc_VoltageSource;

typedef enum
{
  ADC_RIGHT_ADJUST = 0
} Adc_ResultAdjust;

typedef enum
{
  ADC_SINGLE_ENDED_ADC0 = 0b00000,
} Adc_AnalogInputAndGain;

typedef enum
{
  ADC_PRESCALE_FACTOR_2 = 0b001
} Adc_PrescaleFactor;

BOOL Adc_IsAdcBusy(void);
void Adc_StartConversion(void);
BOOL Adc_IsInterruptFlagSet(void);
int8_t Adc_ReadDataRegister_High(void);
int8_t Adc_ReadDataRegister_Low(void);
void Adc_ClearInterruptFlag(void);

//Setup functions
void Adc_SelectReferenceVoltage(Adc_VoltageSource);
void Adc_SelectResultAdjust(Adc_ResultAdjust);
void Adc_SelectInputAndGain(Adc_AnalogInputAndGain);
void Adc_SetPrescaleFactor(Adc_PrescaleFactor);
void Adc_Enable(void);
void Adc_FirstConversion(void); // Run this after enabling the ADC. It does internal initialization.

#endif
