#ifndef ADC_H_
#define ADC_H_

#include "DataTypes.h"
#include <stdint.h>


//This hardware-dependent module is inteded to by used by the AtoD module.
//It is an abstraction layer to keep AtoD from having direct hardware dependencies.
//It is NOT designed to be used directly by the user.
//To use the ADC, refer to AtoD.h


//***********************//
//*** Register Values ***//
//***********************//
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

//**************************//
//*** Standard Functions ***//
//**************************//
BOOL Adc_IsAdcBusy(void);
void Adc_StartConversion(void);
BOOL Adc_IsInterruptFlagSet(void);
uint8_t Adc_ReadDataRegister_High(void);
uint8_t Adc_ReadDataRegister_Low(void);
void Adc_ClearInterruptFlag(void);



//********************//
//*** Setup Values ***//
//********************//
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
  ADC_PRESCALE_FACTOR_0 = 0b000,  //Actually sets it to 2
  ADC_PRESCALE_FACTOR_2 = 0b001
} Adc_PrescaleFactor;

//***********************//
//*** Setup Functions ***//
//***********************//
//Map chip's registers to local pointers.
//Must be called BEFORE Adc_Init!
void Adc_MapMemory(uint8_t * adcsr, uint8_t * admux, uint8_t * adch, uint8_t * adcl);

//Set up the ADC for use.
//Call Adc_MapMemory() BEFORE initialization!
void Adc_Init(void);

//Enable the ADC for use.
//Call after initialization.
void Adc_Enable(void);

//Perform internal chip initialization.
//Execute after enabling the ADC.
void Adc_FirstConversion(void);


//*************************//
//*** Private Functions ***//
//*************************//
//These functions are in the header file only to facilitate in-depth testing
void Adc_Private_SelectReferenceVoltage(Adc_VoltageSource);
void Adc_Private_SelectResultAdjust(Adc_ResultAdjust);
void Adc_Private_SelectInputAndGain(Adc_AnalogInputAndGain);
void Adc_Private_SelectPrescaleFactor(Adc_PrescaleFactor);

#endif
