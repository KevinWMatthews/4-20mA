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
      alarms[i].counter = PA_INACTIVE;
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
  alarm->counter = PA_COUNTER_RESET_VALUE;
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
  int i;

  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    if (&alarms[i] == NULL || alarms[i].callback == NULL)
    {
      continue;
    }
    if (TimeService_Private_IsCallbackTime(&alarms[i]) == TRUE)
    {
      alarms[i].callback();
    }
  }
}

int16_t TimeService_Private_GetCounter(PeriodicAlarm self)
{
  CHECK_NULL_RETURN_VALUE(self, PA_NULL_POINTER);
  return self->counter;
}

BOOL TimeService_Private_IsCallbackTime(PeriodicAlarm self)
{
  CHECK_NULL_RETURN_VALUE(self, FALSE);
  return self->executeCallbackNow;
}

void TimeService_Private_SetExecuteNowFlag(PeriodicAlarm self)
{
  CHECK_NULL(self);
  self->executeCallbackNow = TRUE;
}

void TimeService_Private_IncrementCounter(PeriodicAlarm self)
{
  CHECK_NULL(self);
  self->counter++;
}

void TimeService_Private_SetCounter(PeriodicAlarm self, int16_t value)
{
  CHECK_NULL(self);
  self->counter = value;
}

void TimeService_Private_ResetCounter(PeriodicAlarm self)
{
  CHECK_NULL(self);
  self->counter = 0;
}

void TimeService_InterruptRoutine(void)
{
  int i;

  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    if (TimeService_Private_GetCounter(&alarms[i]) == PA_UNUSED || TimeService_Private_GetCounter(&alarms[i]) == PA_INACTIVE)
    {
      continue;
    }
    TimeService_Private_IncrementCounter(&alarms[i]);
    if (TimeService_Private_GetCounter(&alarms[i]) >= TimeService_GetCallbackInterval(&alarms[i]))
    {
      TimeService_Private_SetExecuteNowFlag(&alarms[i]);
      TimeService_Private_ResetCounter(&alarms[i]);
    }
  }
}
