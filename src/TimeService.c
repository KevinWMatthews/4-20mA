#include "TimeService.h"

//*** Data types ***//
typedef struct PeriodicAlarmStruct
{
  PeriodicCallback callback;
  int16_t period;
} PeriodicAlarmStruct;


//*** File-scope variables ***//
static PeriodicAlarmStruct alarms[MAX_PERIODIC_ALARMS];

//*** File-scope functions ***//
static void clearPeriodicAlarm(PeriodicAlarm alarm)
{
  alarm->callback = NULL;
  alarm->period = -1;
}


//*** Public functions ***//
void TimeService_Create(void)
{
  int i;
  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    clearPeriodicAlarm(alarms+i);
  }
}

void TimeService_Destroy(void)
{
}

PeriodicAlarm TimeService_CreatePeriodicAlarm(void)
{
  return &alarms[0];
}

// void TimeService_SetPeriodicAlarm(PeriodicCallback callbackFunction, int16_t alarmPeriod)
// {
//   callback = callbackFunction;
//   period = alarmPeriod;
// }

// void TimeService_ClearPeriodicAlarm(PeriodicCallback callbackFunction, int16_t alarmPeriod)
// {
//   clearPeriodicAlarm();
// }

PeriodicCallback TimeService_GetCallbackFunction(PeriodicAlarm alarm)
{
  CHECK_NULL_RETURN_VALUE(alarm, NULL);
  return alarm->callback;
}

int16_t TimeService_GetCallbackInterval(PeriodicAlarm alarm)
{
  CHECK_NULL_RETURN_VALUE(alarm, 0);
  return alarm->period;
}
