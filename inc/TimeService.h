#ifndef TimeService_H_
#define TimeService_H_

#include "DataTypes.h"

typedef struct PeriodicAlarmStruct * PeriodicAlarm;

#define MAX_PERIODIC_ALARMS 10

enum {PA_INACTIVE = -1, PA_UNUSED = -2, PA_NULL_POINTER = -3};

//Define a function pointer type.
//Compiler magic!
typedef void (*PeriodicCallback)(void);


//***********************//
//*** Setup Functions ***//
//***********************//

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


//*************************//
//*** Control Functions ***//
//*************************//

//This function executes any callback functions whose alarm period has expired
//It should NOT be called from within an interrupt routine since there is no guarantee that the callbacks execute quickly
//Instead, it should be executed from within a task
void TimeService_ServiceAllCallbacks(void);


//This should be called from within a hardware timer's interrupt routine once per millisecond
//It controls the timer that is used to determine when a callback will be executed
void TimeService_InterruptRoutine(void);

#include "TimeService_Private.h"

#endif
