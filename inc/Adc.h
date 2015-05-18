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

typedef enum
{
  ADC_DISABLED = 0,
  ADC_ENABLED = 1
} Adc_Enabled;

typedef enum
{
  ADC_FREE = 0,
  ADC_BUSY = 1
} Adc_BusyStatus;

//ADMUX - ADC Multiplexer Selection Register
#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX4  4
#define MUX3  3
#define MUX2  2
#define MUX1  1
#define MUX0  0

//ADCSR - ADC Control and Status Register
#define ADEN  7
#define ADSC  6
#define ADIF  5
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

BOOL Adc_IsAdcBusy(void);
void Adc_StartConversion(void);
BOOL Adc_IsInterruptFlagSet(void);
uint8_t Adc_ReadDataRegister_High(void);
uint8_t Adc_ReadDataRegister_Low(void);
void Adc_ClearInterruptFlag(void);

//Setup functions
void Adc_Init(uint8_t * adcsr, uint8_t * admux, uint8_t * adch, uint8_t * adcl);
void Adc_SelectReferenceVoltage(Adc_VoltageSource);
void Adc_SelectResultAdjust(Adc_ResultAdjust);
void Adc_SelectInputAndGain(Adc_AnalogInputAndGain);
void Adc_SetPrescaleFactor(Adc_PrescaleFactor);
void Adc_Enable(void);
void Adc_FirstConversion(void); // Run this after enabling the ADC. It does internal initialization.

#endif
