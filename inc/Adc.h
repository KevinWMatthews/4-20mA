#ifndef Adc_H_
#define Adc_H_

#include <stdint.h>

enum
{
  ADC_CONVERSION_BUSY    = -1,
  ADC_CONVERSION_STARTED = 1
};

enum
{
  // ADC_INTERRUPT_FLAG_NOT_SET = -2,
  ADC_READ_BUSY    = -1,
  ADC_READ_SUCCESS = 1
};

void Adc_Setup(void);
int8_t Adc_StartConversion(void);
int8_t Adc_Read(int16_t * adcReading);

#endif
