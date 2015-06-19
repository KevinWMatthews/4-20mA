#ifndef TimeService_Private_H_
#define TimeService_Private_H_

#include "DataTypes.h"
#include "TimeService.h"    //Wait, what? Can I do this?

typedef struct PeriodicAlarmStruct
{
  PeriodicCallback callback;
  int16_t period;
  int16_t counter;
  BOOL executeNow;
} PeriodicAlarmStruct;

#endif
