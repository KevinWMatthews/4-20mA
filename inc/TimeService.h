#ifndef TimeService_H_
#define TimeService_H_

#include "DataTypes.h"

typedef struct PeriodicAlarmStruct * PeriodicAlarm;

#define MAX_PERIODIC_ALARMS 10

enum {PA_UNUSED = -1};

//Define a function pointer type.
//Compiler magic!
typedef void (*PeriodicCallback)(void);

void TimeService_Create(void);
void TimeService_Destroy(void);

//Returns a pointer to the periodic alarm
//Mark this alarm as in use but disabled
PeriodicAlarm TimeService_AddPeriodicAlarm(void);

//It is the user's responsibility to discard pointer after the alarm is removed
//Sets the callback to NULL and the period to PA_UNUSED
void TimeService_RemovePeriodicAlarm(PeriodicAlarm alarm);

//Once set, periodic alarms always executed
//To disable a periodic alarm, set its period to 0
void TimeService_SetPeriodicAlarm(PeriodicAlarm alarm, PeriodicCallback callbackFunction, int16_t alarmPeriod);

PeriodicCallback TimeService_GetCallbackFunction(PeriodicAlarm alarm);
int16_t TimeService_GetCallbackInterval(PeriodicAlarm alarm);

void TimeService_ServiceAllCallbacks(void);

#include "TimeService_Private.h"

#endif
