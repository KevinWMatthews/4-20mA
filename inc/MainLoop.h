#ifndef MainLoop_H_
#define MainLoop_H_

#include "TimeService.h"
#include "LineFit.h"
#include "LedNumber.h"
#include "DataTypes.h"

//Prototypes for callbacks
void MainLoop_AdcConversion(void * param);
void MainLoop_GetReading(void * param);
void MainLoop_UpdateDisplay(void * param);

typedef struct getReadingParameterStruct
{
  LineFit outputModel;            //Map ADC raw counts to desired output
  LedNumber ledDisplay;
  PeriodicAlarm getReadingAlarm;  //The alarm for this callback function
} getReadingParameterStruct;

//A hack so that we can "pass data" to a callback.
void MainLoop_Init(PeriodicAlarm adcRead, LedNumber number, LineFit line);

int8_t MainLoop_GetAdcConversionStatus(void);


//Included to make testing easier.
//If you have a need to use these then you're probably doing something wrong.
void MainLoop_Private_SetAdcConversionStatus(int8_t value);

#endif
