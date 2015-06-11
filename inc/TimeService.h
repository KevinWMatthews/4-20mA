#ifndef TimeService_H_
#define TimeService_H_

#include "DataTypes.h"

//Define a function pointer type.
//Compiler magic!
typedef void (*PeriodicCallback)(void);

void TimeService_Create(void);
void TimeService_Destroy(void);

void TimeService_SetPeriodicAlarm(PeriodicCallback callbackFunction, int16_t alarmPeriod);
PeriodicCallback TimeService_GetCallbackFunction(void);
int16_t TimeService_GetCallbackInterval(void);

#endif
