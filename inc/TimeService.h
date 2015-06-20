#ifndef TimeService_H_
#define TimeService_H_

#include "DataTypes.h"

typedef struct PeriodicAlarmStruct * PeriodicAlarm;

#define MAX_PERIODIC_ALARMS 10

enum {PA_INACTIVE = -1, PA_UNUSED = -2, PA_NULL_POINTER = -3};

//Define a function pointer type for the callback.
//Compiler magic!
typedef void (*PeriodicAlarmCallback)(void);



//***********************//
//*** Setup Functions ***//
//***********************//
//Creates and initializes the TimeService as a whole.
//No alarms are created; they must be added individually by the user.
void TimeService_Create(void);

//Resets the time service as a whole, destroying all alarms.
//It is the user's responsibility to discard all PeriodicAlarm pointers
//after the TimeService is destroyed,
//although the program shouldn't crash if you do.
void TimeService_Destroy(void);

//Creates and returns a pointer to a new periodic alarm.
//This alarm will be marked as inactive until it is set.
PeriodicAlarm TimeService_AddPeriodicAlarm(PeriodicAlarmCallback callback, int16_t period);

//Removes the given alarm from the TimeService.
//It is the user's responsibility to discard the pointer after the alarm is removed,
//although the program shouldn't crash if you do.
void TimeService_RemovePeriodicAlarm(PeriodicAlarm self);

//Once set, the periodic alarm always serviced.
//To stop a periodic alarm from executing, set its period to PA_INACTIVE.
void TimeService_ActivatePeriodicAlarm(PeriodicAlarm self);


//*************************//
//*** Control Functions ***//
//*************************//
//Execute any callback functions whose alarm period has expired.
//This function should NOT be called from within an interrupt routine
//because there is no guarantee that callbacks will execute quickly.
//Instead, it should be executed from within a task or the main loop.
void TimeService_ServiceAllCallbacks(void);


//Increment and check alarm timers.
//This function should be called once per millisecond.
//It is designed to be executed from within an interrupt routine.
void TimeService_TimerTick(void);

#include "TimeService_Private.h"

#endif
