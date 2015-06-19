#include "TimeService.h"


//*** File-scope variables ***//
static PeriodicAlarmStruct alarms[MAX_PERIODIC_ALARMS];


//*** File-scope functions ***//
static void markSingleAlarmAsUnused(PeriodicAlarm alarm)
{
  alarm->callback = NULL;
  alarm->period = PA_UNUSED;
  alarm->counter = PA_UNUSED;
  alarm->executeCallbackNow = FALSE;
}

static void markAllAlarmsAsUnused(void)
{
  int i;
  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    markSingleAlarmAsUnused(&alarms[i]);
  }
}


//*** Public functions ***//


//***********************//
//*** Setup Functions ***//
//***********************//

void TimeService_Create(void)
{
  markAllAlarmsAsUnused();
}

void TimeService_Destroy(void)
{
  markAllAlarmsAsUnused();
}

PeriodicAlarm TimeService_AddPeriodicAlarm(void)
{
  int i;

  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    if (alarms[i].period == PA_UNUSED)
    {
      alarms[i].period = PA_INACTIVE;
      TimeService_ResetCounter(&alarms[i]);
      return &alarms[i];
    }
  }
  return NULL;
}

void TimeService_RemovePeriodicAlarm(PeriodicAlarm alarm)
{
  CHECK_NULL(alarm);
  markSingleAlarmAsUnused(alarm);
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
  CHECK_NULL_RETURN_VALUE(alarm, PA_NULL_POINTER);
  return alarm->period;
}


//*************************//
//*** Control Functions ***//
//*************************//

void TimeService_ServiceAllCallbacks(void)
{
  CHECK_NULL(&alarms[0]);
  CHECK_NULL(alarms[0].callback);

  if (TimeService_IsCallbackTime(&alarms[0]) == TRUE)
  {
    alarms[0].callback();
  }
}

int16_t TimeService_GetCounter(PeriodicAlarm self)
{
  CHECK_NULL_RETURN_VALUE(self, PA_NULL_POINTER);
  return self->counter;
}

BOOL TimeService_IsCallbackTime(PeriodicAlarm self)
{
  CHECK_NULL_RETURN_VALUE(self, FALSE);
  return self->executeCallbackNow;
}

void TimeService_SetExecuteNowFlag(PeriodicAlarm self)
{
  CHECK_NULL(self);
  self->executeCallbackNow = TRUE;
}

void TimeService_IncrementCounter(PeriodicAlarm self)
{
  CHECK_NULL(self);
  self->counter++;
}

void TimeService_SetCounter(PeriodicAlarm self, int16_t value)
{
  CHECK_NULL(self);
  self->counter = value;
}

void TimeService_ResetCounter(PeriodicAlarm self)
{
  CHECK_NULL(self);
  self->counter = 0;
}

void TimeService_InterruptRoutine(void)
{
  TimeService_IncrementCounter(&alarms[0]);
  if (TimeService_GetCounter(&alarms[0]) >= TimeService_GetCallbackInterval(&alarms[0]))
  {
    TimeService_SetExecuteNowFlag(&alarms[0]);
    TimeService_ResetCounter(&alarms[0]);
  }
}
