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

static void clearAllPeriodicAlarms(void)
{
  int i;
  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    clearPeriodicAlarm(alarms+i);
  }
}


//*** Public functions ***//
void TimeService_Create(void)
{
  clearAllPeriodicAlarms();
}

void TimeService_Destroy(void)
{
  clearAllPeriodicAlarms();
}

PeriodicAlarm TimeService_CreatePeriodicAlarm(void)
{
  return &alarms[0];
}

void TimeService_SetPeriodicAlarm(PeriodicAlarm alarm, PeriodicCallback callbackFunction, int16_t alarmPeriod)
{
  CHECK_NULL(alarm);
  alarm->callback = callbackFunction;
  alarm->period = alarmPeriod;
}

void TimeService_ClearPeriodicAlarm(PeriodicAlarm alarm)
{
  CHECK_NULL(alarm);
  clearPeriodicAlarm(alarm);
}

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
