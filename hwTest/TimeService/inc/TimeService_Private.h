#ifndef TimeService_Private_H_
#define TimeService_Private_H_

#include "DataTypes.h"
#include "TimeService.h"    //Wait, what? I can do this? Whoa!

//*** These header file is for test code only!! ***//
//It was created solely to make it easier to spy on and test this module
//Please be object-oriented, my friend.
//In other words, mess up your own code.


typedef struct PeriodicAlarmStruct
{
  PeriodicAlarmCallback callback;
  int16_t period;
  int16_t counter;
  BOOL executeCallbackNow;
} PeriodicAlarmStruct;

enum {PA_COUNTER_RESET_VALUE = 0};

//GO AWAY!
//I think my design pattern is off so I have to use these.
//Rather than using these, read a book about object-oriented design and fix my design.
PeriodicAlarmCallback TimeService_Private_GetCallback(PeriodicAlarm self);
int16_t TimeService_Private_GetPeriod(PeriodicAlarm self);
void TimeService_Private_SetCounter(PeriodicAlarm self, int16_t value);
int16_t TimeService_Private_GetCounter(PeriodicAlarm self);
BOOL TimeService_Private_IsCallbackTime(PeriodicAlarm self);

#endif
