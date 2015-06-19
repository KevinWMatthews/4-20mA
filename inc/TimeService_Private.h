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


//Declare as function pointer so we can point it to our fake during testing
extern int16_t (*TimeService_GetCounter)(PeriodicAlarm self);
BOOL TimeService_IsCallbackTime(PeriodicAlarm self);
extern void (*TimeService_IncrementCounter)(PeriodicAlarm self);
extern void (*TimeService_ResetCounter)(PeriodicAlarm self);

#endif
