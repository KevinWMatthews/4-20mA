#include "TimeService.h"



//****************************//
//*** File-scope variables ***//
//****************************//
static PeriodicAlarmStruct alarms[MAX_PERIODIC_ALARMS];



//****************************//
//*** File-scope functions ***//
//****************************//
static void setCallback(PeriodicAlarm self, PeriodicAlarmCallback callback)
{
  CHECK_NULL(self);
  self->callback = callback;
}

static PeriodicAlarmCallback getCallback(PeriodicAlarm self)
{
  CHECK_NULL_RETURN_VALUE(self, NULL);
  return self->callback;
}

static void setPeriod(PeriodicAlarm self, int16_t period)
{
  CHECK_NULL(self);
  self->period = period;
}

static int16_t getPeriod(PeriodicAlarm self)
{
  CHECK_NULL_RETURN_VALUE(self, PA_NULL_POINTER);
  return self->period;
}

static void setCounter(PeriodicAlarm self, int16_t counter)
{
  CHECK_NULL(self);
  self->counter = counter;
}

static int16_t getCounter(PeriodicAlarm self)
{
  CHECK_NULL_RETURN_VALUE(self, PA_NULL_POINTER);
  return self->counter;
}

static void resetCounter(PeriodicAlarm self)
{
  setCounter(self, PA_COUNTER_RESET_VALUE);
}

static void incrementCounter(PeriodicAlarm self)
{
  CHECK_NULL(self);
  self->counter++;
}

static void setExecuteCallbackNowFlag(PeriodicAlarm self, BOOL executeCallbackNow)
{
  CHECK_NULL(self);
  self->executeCallbackNow = executeCallbackNow;
}

static BOOL getExecuteCallbackNowFlag(PeriodicAlarm self)
{
  CHECK_NULL_RETURN_VALUE(self, FALSE);
  return self->executeCallbackNow;
}

static void markSingleAlarmAsUnused(PeriodicAlarm self)
{
  setCallback(self, NULL);
  setPeriod(self, PA_UNUSED);
  setCounter(self, PA_UNUSED);
  setExecuteCallbackNowFlag(self, FALSE);
}

static void markAllAlarmsAsUnused(void)
{
  int i;
  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    markSingleAlarmAsUnused(&alarms[i]);
  }
}

static BOOL isCounterEnabled(PeriodicAlarm self)
{
  return !(getCounter(self) == PA_UNUSED) &&
         !(getCounter(self) == PA_INACTIVE);
}

static void executeCallback(PeriodicAlarm self, void * params)
{
  CHECK_NULL(self);
  CHECK_NULL(self->callback);
  self->callback(params);
}


//*************************//
//*** Private functions ***//
//*************************//
//Making it easier to spy on and test this module
//I added an extra layer of abstraction to make it easier to modify (hopefully)
//Maybe I'll discover a better way to test the module, in which case I'll modify these Private functions
//while leaving the file's static functions alone.
PeriodicAlarmCallback TimeService_Private_GetCallback(PeriodicAlarm self)
{
  return getCallback(self);
}

int16_t TimeService_Private_GetPeriod(PeriodicAlarm self)
{
  return getPeriod(self);
}

void TimeService_Private_SetCounter(PeriodicAlarm self, int16_t value)
{
  setCounter(self, value);
}

int16_t TimeService_Private_GetCounter(PeriodicAlarm self)
{
  return getCounter(self);
}

BOOL TimeService_Private_IsCallbackTime(PeriodicAlarm self)
{
  return getExecuteCallbackNowFlag(self);
}



//************************//
//*** Public Functions ***//
//************************//
void TimeService_Create(void)
{
  markAllAlarmsAsUnused();
}

void TimeService_Destroy(void)
{
  markAllAlarmsAsUnused();
}

PeriodicAlarm TimeService_AddPeriodicAlarm(PeriodicAlarmCallback callback, int16_t period)
{
  PeriodicAlarm thisAlarm;
  int i;

  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    thisAlarm = &alarms[i];
    if (getPeriod(thisAlarm) == PA_UNUSED)
    {
      setCallback(thisAlarm, callback);
      setPeriod(thisAlarm, period);
      setCounter(thisAlarm, PA_INACTIVE);
      return thisAlarm;
    }
  }
  return NULL;
}

void TimeService_RemovePeriodicAlarm(PeriodicAlarm self)
{
  markSingleAlarmAsUnused(self);
}

void TimeService_ActivatePeriodicAlarm(PeriodicAlarm self)
{
  setCounter(self, PA_COUNTER_RESET_VALUE);
}

void TimeService_DeactivatePeriodicAlarm(PeriodicAlarm self)
{
  setCounter(self, PA_INACTIVE);
}

void TimeService_ServiceSingleCallback(PeriodicAlarm self, void * params)
{
  if (getExecuteCallbackNowFlag(self) == TRUE)
  {
    executeCallback(self, params);
    setExecuteCallbackNowFlag(self, FALSE);
  }
}

void TimeService_TimerTick(void)
{
  PeriodicAlarm thisAlarm;
  int i;

  for (i = 0; i < MAX_PERIODIC_ALARMS; i++)
  {
    thisAlarm = &alarms[i];
    if (!isCounterEnabled(thisAlarm))
    {
      continue;
    }
    incrementCounter(thisAlarm);
    if (getCounter(thisAlarm) >= getPeriod(thisAlarm))
    {
      setExecuteCallbackNowFlag(thisAlarm, TRUE);
      resetCounter(thisAlarm);
    }
  }
}
