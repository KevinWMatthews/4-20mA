#ifndef TimeService_H_
#define TimeService_H_

#include "DataTypes.h"

typedef struct PeriodicAlarmStruct * PeriodicAlarm;

#define MAX_PERIODIC_ALARMS 1

//Define a function pointer type.
//Compiler magic!
typedef void (*PeriodicCallback)(void);

void TimeService_Create(void);
void TimeService_Destroy(void);

PeriodicAlarm TimeService_CreatePeriodicAlarm(void);
void TimeService_SetPeriodicAlarm(PeriodicAlarm alarm, PeriodicCallback callbackFunction, int16_t alarmPeriod);
void TimeService_ClearPeriodicAlarm(PeriodicAlarm alarm);
PeriodicCallback TimeService_GetCallbackFunction(PeriodicAlarm alarm);
int16_t TimeService_GetCallbackInterval(PeriodicAlarm alarm);

#endif
