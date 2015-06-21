#ifndef MainLoop_H_
#define MainLoop_H_

#include "TimeService.h"
#include "LineFit.h"
#include "LedNumber.h"
#include "DataTypes.h"

//Prototypes for callbacks
void MainLoop_AtodConversion(void);
void MainLoop_UpdateDisplay(void);
void MainLoop_GetReading(void);


//A hack so that we can "pass data" to a callback.
void MainLoop_Init(PeriodicAlarm atodRead, LedNumber number, LineFit line);

int8_t MainLoop_GetAtodConversionStatus(void);


//Included to make testing easier.
//If you have a need to use these then you're probably doing something wrong.
void MainLoop_Private_SetAtodConversionStatus(int8_t value);

#endif
