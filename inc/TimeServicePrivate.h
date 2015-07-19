#ifndef TimeServicePrivate_H_
#define TimeServicePrivate_H_

#include "DataTypes.h"
#include "TimeService.h"    //Wait, what? I can do this? Whoa!



//**************************************//
//*** This is a private interface!!! ***//
//**************************************//
//It is inteded to be used solely by its public module and by test code.
//It was created purely to make it easier to spy on and test this module.
//It is not inteded for the user.
//Unless it is broken, GO AWAY!

//These functions are implemented in TimeService.c


typedef struct PeriodicAlarmStruct
{
  PeriodicAlarmCallback callback;
  int16_t period;
  int16_t counter;
  BOOL executeInIsr;
  BOOL executeCallbackNow;
} PeriodicAlarmStruct;


enum {PA_COUNTER_RESET_VALUE = 0, PA_INACTIVE = -1, PA_UNUSED = -2, PA_NULL_POINTER = -3};



//GO AWAY!
//I think my design pattern is bad so I have to use these.
//Rather than using these, read a book about object-oriented design and fix my design.
PeriodicAlarmCallback TimeServicePrivate_GetCallback(PeriodicAlarm self);
int16_t TimeServicePrivate_GetPeriod(PeriodicAlarm self);
void TimeServicePrivate_SetCounter(PeriodicAlarm self, int16_t value);
int16_t TimeServicePrivate_GetCounter(PeriodicAlarm self);
BOOL TimeServicePrivate_GetExecuteCallbackFlag(PeriodicAlarm self);
void TimeServicePrivate_SetExecuteCallbackFlag(PeriodicAlarm self, BOOL executeCallbackNow);



#endif
