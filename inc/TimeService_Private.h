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

enum {PA_COUNTER_RESET_VALUE = 0};

int16_t TimeService_Private_GetCounter(PeriodicAlarm self);
void TimeService_Private_SetCounter(PeriodicAlarm self, int16_t value);
BOOL TimeService_Private_IsCallbackTime(PeriodicAlarm self);
void TimeService_Private_IncrementCounter(PeriodicAlarm self);
void TimeService_Private_ResetCounter(PeriodicAlarm self);
void TimeService_Private_SetExecuteNowFlag(PeriodicAlarm self);

#endif
