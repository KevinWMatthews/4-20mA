#ifndef MainLoop_H_
#define MainLoop_H_

#include "LineFit.h"
#include "LedNumber.h"
#include "DataTypes.h"

//Prototypes for callbacks
void MainLoop_AtodConversion(void);
void MainLoop_UpdateDisplay(void);

int8_t MainLoop_GetAtodConversionStatus(void);

void MainLoop_GetReading(LedNumber ledDisplay, LineFit outputModel);

//Included to make testing easier.
//If you have a need to use these then you're probably doing something wrong.
void MainLoop_Private_SetAtodConversionStatus(int8_t value);

#endif
