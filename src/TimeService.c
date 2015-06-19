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

// void TimeService_ServiceAllCallbacks(void)
// {

// }

//*** Interrupt ***//
int16_t TimeService_GetCounter_Impl(PeriodicAlarm self)
{
  CHECK_NULL_RETURN_VALUE(self, PA_NULL_POINTER);
  return self->counter;
}

//Point function pointer to the standard implementation
int16_t (*TimeService_GetCounter)(PeriodicAlarm self) = TimeService_GetCounter_Impl;

BOOL TimeService_IsCallbackTime(PeriodicAlarm self)
{
  CHECK_NULL_RETURN_VALUE(self, FALSE);
  return self->executeCallbackNow;
}

void TimeService_IncrementCounter_Impl(PeriodicAlarm self)
{
}

void (*TimeService_IncrementCounter)(PeriodicAlarm self) = TimeService_IncrementCounter_Impl;

void TimeService_ResetCounter_Impl(PeriodicAlarm self)
{
  //TODO NULL check
  self->counter = 0;
}

void (*TimeService_ResetCounter)(PeriodicAlarm self) = TimeService_ResetCounter_Impl;

void TimeService_InterruptRoutine(PeriodicAlarm self)
{
  //TODO NULL check
  TimeService_IncrementCounter(self);
  if (TimeService_GetCounter(self) >= self->period)
  {
    self->executeCallbackNow = TRUE;
    TimeService_ResetCounter(self);
  }
}
