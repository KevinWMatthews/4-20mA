#ifndef ADC_H_
#define ADC_H_

#include "DataTypes.h"

//Registers in ADCSR - ADC Control and Status Register
#define ADSC (1<<6)
#define ADIF (1<<4)

BOOL isAdcBusy(void);
void startConversion(void);
BOOL isInterruptFlagSet(void);

#endif
