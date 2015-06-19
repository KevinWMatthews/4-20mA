#ifndef TimeService_Private_H_
#define TimeService_Private_H_

#include "DataTypes.h"
#include "TimeService.h"    //Wait, what? Can I do this?

typedef struct PeriodicAlarmStruct
{
  PeriodicCallback callback;
  int16_t period;
  int16_t counter;
  BOOL executeCallbackNow;
} PeriodicAlarmStruct;


int16_t TimeService_GetCounter(PeriodicAlarm self);
void TimeService_SetCounter(PeriodicAlarm self, int16_t value);
BOOL TimeService_IsCallbackTime(PeriodicAlarm self);
void TimeService_IncrementCounter(PeriodicAlarm self);
void TimeService_ResetCounter(PeriodicAlarm self);
void TimeService_SetExecuteNowFlag(PeriodicAlarm self);

#endif
