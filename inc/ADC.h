#ifndef ADC_H_
#define ADC_H_

#include "DataTypes.h"

//Registers in ADCSR - ADC Control and Status Register
#define ADSC (1<<6)

BOOL isAdcBusy(void);

#endif
