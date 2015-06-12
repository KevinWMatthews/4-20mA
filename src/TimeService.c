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
static void markAlarmAsUnused(PeriodicAlarm alarm)
{
  alarm->callback = NULL;
  alarm->period = PA_UNUSED;
}

static void markAllAlarmAsUnused(void)
{
  int i;
  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    markAlarmAsUnused(&alarms[i]);
  }
}


//*** Public functions ***//
void TimeService_Create(void)
{
  markAllAlarmAsUnused();
}

void TimeService_Destroy(void)
{
  markAllAlarmAsUnused();
}

PeriodicAlarm TimeService_AddPeriodicAlarm(void)
{
  int i;

  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    if (alarms[i].period == PA_UNUSED)
    {
      alarms[i].period = 0;
      return &alarms[i];
    }
  }
  return NULL;
}

void TimeService_RemovePeriodicAlarm(PeriodicAlarm alarm)
{
  CHECK_NULL(alarm);
  markAlarmAsUnused(alarm);
}

void TimeService_SetPeriodicAlarm(PeriodicAlarm alarm, PeriodicCallback callbackFunction, int16_t alarmPeriod)
{
  CHECK_NULL(alarm);
  alarm->callback = callbackFunction;
  alarm->period = alarmPeriod;
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
