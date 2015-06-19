#ifndef TimeService_H_
#define TimeService_H_

#include "DataTypes.h"

typedef struct PeriodicAlarmStruct * PeriodicAlarm;

#define MAX_PERIODIC_ALARMS 10

enum {PA_INACTIVE = 0, PA_UNUSED = -1, PA_NULL_POINTER = -2};

//Define a function pointer type.
//Compiler magic!
typedef void (*PeriodicCallback)(void);

//Creates the time service as a whole
//All alarms are unused
void TimeService_Create(void);

//Resets the time service as a whole
//All alarms are unused
void TimeService_Destroy(void);

//Returns a pointer to the periodic alarm
//This alarm will be marked as in use but inactive:
//  callback = NULL
//  period = PA_INACTIVE
PeriodicAlarm TimeService_AddPeriodicAlarm(void);

//Removes the given alarm from the TimeService
//  callback = NULL
//  period = PA_UNUSED
//It is the user's responsibility to discard pointer after the alarm is removed
void TimeService_RemovePeriodicAlarm(PeriodicAlarm alarm);

//Once set, the periodic alarm always serviced
//To stop a periodic alarm from executing, set its period to PA_INACTIVE
void TimeService_SetPeriodicAlarm(PeriodicAlarm alarm, PeriodicCallback callbackFunction, int16_t alarmPeriod);

//Query the details of a particular alarm
PeriodicCallback TimeService_GetCallbackFunction(PeriodicAlarm alarm);
int16_t TimeService_GetCallbackInterval(PeriodicAlarm alarm);

// void TimeService_ServiceAllCallbacks(void);


//This interrupt routine should be called once per millisecond
//It shold be called once for each alarm
//It controls the timer that is used to determine when the callback will be executed
void TimeService_InterruptRoutine(PeriodicAlarm self);

#include "TimeService_Private.h"

#endif
