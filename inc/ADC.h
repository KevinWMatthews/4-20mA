#ifndef ADC_H_
#define ADC_H_

#include "DataTypes.h"
#include <stdint.h>

BOOL Adc_IsAdcBusy(void);
void Adc_StartConversion(void);
BOOL Adc_IsInterruptFlagSet(void);
int8_t Adc_ReadDataRegister_High(void);
int8_t Adc_ReadDataRegister_Low(void);
void Adc_ClearInterruptFlag(void);

#endif
