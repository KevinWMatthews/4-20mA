#ifndef AdcWiring_H_
#define AdcWiring_H_

#include "DataTypes.h"


//This hardware-dependent module is inteded to by used by the Adc module only.
//It is an abstraction layer to keep ADC from having direct hardware dependencies.
//It is NOT designed to be used directly by the user.
//To use the ADC, refer to Adc.h
//In other words, unless the ADC broken, GO AWAY!



//************************//
//*** Public Functions ***//
//************************//
//Set up the ADC for use.
void AdcWiring_HwSetup(void);

//Enable the ADC for use.
//Call after initialization.
void AdcWiring_Enable(void);

//Perform internal chip initialization.
//Execute after enabling the ADC.
void AdcWiring_FirstConversion(void);

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
  ADC_AVCC               = 0b00,
  ADC_AREF_PIN           = 0b01,
  ADC_INTERNAL_NO_AREF   = 0b10,
  ADC_INTERNAL_WITH_AREF = 0b11
} Adc_VoltageSource;
#define ADC_VOLTAGE_SOURCE_BITMASK ((1<<REFS1) | (1<<REFS0))

typedef enum
{
  ADC_RIGHT_ADJUST = 0,
  ADC_LEFT_ADJUST  = 1
} Adc_ResultAdjust;
#define ADC_RESULT_ADJUST_BITMASK (1<<ADLAR)

typedef enum
{
  ADC_SINGLE_ENDED_ADC0 = 0b00000,
  ADC_GROUND            = 0b11111
} Adc_AnalogInputAndGain;
#define ADC_ANALOG_INPUT_AND_GAIN_BITMASK ((1<<MUX4) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1)| (1<<MUX0))

typedef enum
{
  ADC_PRESCALE_FACTOR_0   = 0b000,  //Actually sets it to 2
  ADC_PRESCALE_FACTOR_2   = 0b001,
  ADC_PRESCALE_FACTOR_64  = 0b110,
  ADC_PRESCALE_FACTOR_128 = 0b111
} Adc_PrescaleFactor;
#define ADC_PRESCALE_FACTOR_BITMASK ((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0))


//*************************//
//*** Private Functions ***//
//*************************//
//These functions are in the header file only to facilitate in-depth testing
void AdcWiring_Private_SelectReferenceVoltage(Adc_VoltageSource);
void AdcWiring_Private_SelectResultAdjust(Adc_ResultAdjust);
void AdcWiring_Private_SelectInputAndGain(Adc_AnalogInputAndGain);
void AdcWiring_Private_SelectPrescaleFactor(Adc_PrescaleFactor);



#endif
