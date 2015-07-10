#ifndef TimeService_Private_H_
#define TimeService_Private_H_

#include "DataTypes.h"
#include "TimeService.h"    //Wait, what? I can do this? Whoa!



//**************************************//
//*** This is a private interface!!! ***//
//**************************************//
//It is inteded to be used solely by its public module and by test code.
//It was created purely to make it easier to spy on and test this module.
//It is not inteded for the user.
//Unless it is broken, GO AWAY!



typedef struct PeriodicAlarmStruct
{
  PeriodicAlarmCallback callback;
  int16_t period;
  int16_t counter;
  BOOL executeCallbackNow;
} PeriodicAlarmStruct;

enum {PA_COUNTER_RESET_VALUE = 0};



//GO AWAY!
//I think my design pattern is bad so I have to use these.
//Rather than using these, read a book about object-oriented design and fix my design.
PeriodicAlarmCallback TimeService_Private_GetCallback(PeriodicAlarm self);
int16_t TimeService_Private_GetPeriod(PeriodicAlarm self);
void TimeService_Private_SetCounter(PeriodicAlarm self, int16_t value);
int16_t TimeService_Private_GetCounter(PeriodicAlarm self);
BOOL TimeService_Private_IsCallbackTime(PeriodicAlarm self);



#endif
