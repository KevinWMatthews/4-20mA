#ifndef AdcWiring_H_
#define AdcWiring_H_

#include "DataTypes.h"


//This hardware-dependent module is inteded to by used by the Adc module.
//It is an abstraction layer to keep Adc from having direct hardware dependencies.
//It is NOT designed to be used directly by the user.
//To use the ADC, refer to Adc.h


//***********************//
//*** Register Values ***//
//***********************//
typedef enum
{
  ADC_FREE = 0,
  ADC_BUSY = 1
} Adc_BusyStatus;

//**************************//
//*** Standard Functions ***//
//**************************//
BOOL AdcWiring_IsAdcBusy(void);
void AdcWiring_StartConversion(void);
BOOL AdcWiring_IsInterruptFlagSet(void);
uint8_t AdcWiring_ReadDataRegister_High(void);
uint8_t AdcWiring_ReadDataRegister_Low(void);
void AdcWiring_ClearInterruptFlag(void);



//********************//
//*** Setup Values ***//
//********************//
typedef enum
{
  ADC_AVCC            = 0b00,
  ADC_AREF_PIN        = 0b01,
  ADC_INTERNAL_NO_PA3 = 0b10
} Adc_VoltageSource;

typedef enum
{
  ADC_RIGHT_ADJUST = 0,
  ADC_LEFT_ADJUST  = 1
} Adc_ResultAdjust;

typedef enum
{
  ADC_SINGLE_ENDED_ADC0 = 0b00000,
} Adc_AnalogInputAndGain;

typedef enum
{
  ADC_PRESCALE_FACTOR_0  = 0b000,  //Actually sets it to 2
  ADC_PRESCALE_FACTOR_2  = 0b001,
  ADC_PRESCALE_FACTOR_64 = 0b110
} Adc_PrescaleFactor;

//***********************//
//*** Setup Functions ***//
//***********************//
//Set up the ADC for use.
void AdcWiring_Init(void);

//Enable the ADC for use.
//Call after initialization.
void AdcWiring_Enable(void);

//Perform internal chip initialization.
//Execute after enabling the ADC.
void AdcWiring_FirstConversion(void);


//*************************//
//*** Private Functions ***//
//*************************//
//These functions are in the header file only to facilitate in-depth testing
void AdcWiring_Private_SelectReferenceVoltage(Adc_VoltageSource);
void AdcWiring_Private_SelectResultAdjust(Adc_ResultAdjust);
void AdcWiring_Private_SelectInputAndGain(Adc_AnalogInputAndGain);
void AdcWiring_Private_SelectPrescaleFactor(Adc_PrescaleFactor);

#endif
