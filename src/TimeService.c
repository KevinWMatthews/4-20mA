#include "TimeService.h"

static PeriodicCallback callback;
static int16_t period;

static void clearPeriodicAlarm(void)
{
  callback = NULL;
  period = -1;
}

void TimeService_Create(void)
{
  clearPeriodicAlarm();
}

void TimeService_Destroy(void)
{
  clearPeriodicAlarm();
}

void TimeService_SetPeriodicAlarm(PeriodicCallback callbackFunction, int16_t alarmPeriod)
{
  callback = callbackFunction;
  period = alarmPeriod;
}

void TimeService_ClearPeriodicAlarm(PeriodicCallback callbackFunction, int16_t alarmPeriod)
{
  clearPeriodicAlarm();
}

PeriodicCallback TimeService_GetCallbackFunction(void)
{
  return callback;
}

int16_t TimeService_GetCallbackInterval(void)
{
  return period;
}
