#ifndef ADC_H_
#define ADC_H_

#include "DataTypes.h"
#include <stdint.h>

BOOL Adc_IsAdcBusy(void);
void Adc_StartConversion(void);
BOOL Adc_IsInterruptFlagSet(void);
int16_t Adc_ReadDataRegisters(void);
void Adc_ClearInterruptFlag(void);

#endif
