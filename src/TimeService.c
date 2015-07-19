#include "TimeService.h"
#include "TimeServiceWiring.h"

//This is a single-instance module.



//****************************//
//*** File-scope Variables ***//
//****************************//
static PeriodicAlarmStruct alarms[MAX_PERIODIC_ALARMS];



//****************************//
//*** File-scope Functions ***//
//****************************//
static void setCallback(PeriodicAlarm self, PeriodicAlarmCallback callback)
{
  RETURN_IF_NULL(self);
  self->callback = callback;
}

static PeriodicAlarmCallback getCallback(PeriodicAlarm self)
{
  RETURN_VALUE_IF_NULL(self, NULL);
  return self->callback;
}

static void setPeriod(PeriodicAlarm self, int16_t period)
{
  RETURN_IF_NULL(self);
  self->period = period;
}

static int16_t getPeriod(PeriodicAlarm self)
{
  RETURN_VALUE_IF_NULL(self, PA_NULL_POINTER);
  return self->period;
}

static void setCounter(PeriodicAlarm self, int16_t counter)
{
  RETURN_IF_NULL(self);
  self->counter = counter;
}

static int16_t getCounter(PeriodicAlarm self)
{
  RETURN_VALUE_IF_NULL(self, PA_NULL_POINTER);
  return self->counter;
}

static void resetCounter(PeriodicAlarm self)
{
  setCounter(self, PA_COUNTER_RESET_VALUE);
}

static void incrementCounter(PeriodicAlarm self)
{
  RETURN_IF_NULL(self);
  self->counter++;
}

static void setExecuteCallbackNowFlag(PeriodicAlarm self, BOOL executeCallbackNow)
{
  RETURN_IF_NULL(self);
  self->executeCallbackNow = executeCallbackNow;
}

static BOOL getExecuteCallbackNowFlag(PeriodicAlarm self)
{
  RETURN_VALUE_IF_NULL(self, FALSE);
  return self->executeCallbackNow;
}

static void setExecuteInIsrFlag(PeriodicAlarm self, BOOL executeInIsr)
{
  RETURN_IF_NULL(self);
  self->executeInIsr = executeInIsr;
}

static BOOL getExecuteInIsrFlag(PeriodicAlarm self)
{
  RETURN_VALUE_IF_NULL(self, FALSE);
  return self->executeInIsr;
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
  int16_t result;

  result = getCounter(self);
  if (result == PA_UNUSED)
  {
    return FALSE;
  }
  if (result == PA_INACTIVE)
  {
    return FALSE;
  }
  if (result == PA_NULL_POINTER)
  {
    return FALSE;
  }
  return TRUE;
}

static void executeCallback(PeriodicAlarm self, void * params)
{
  RETURN_IF_NULL(self);
  RETURN_IF_NULL(self->callback);
  self->callback(params);
}



//************************//
//*** Public Functions ***//
//************************//
void TimeService_HwSetup(void)
{
  TimeServiceWiring_HardwareSetup();
}

void TimeService_Create(void)
{
  markAllAlarmsAsUnused();
}

void TimeService_Destroy(void)
{
  markAllAlarmsAsUnused();
}

PeriodicAlarm TimeService_AddPeriodicAlarm(PeriodicAlarmCallback callback, int16_t period, BOOL executeInIsr)
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
      setExecuteInIsrFlag(thisAlarm, executeInIsr);
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
      resetCounter(thisAlarm);
      if (getExecuteInIsrFlag(thisAlarm))
      {
        executeCallback(thisAlarm, NULL);
      }
      else
      {
        setExecuteCallbackNowFlag(thisAlarm, TRUE);
      }
    }
  }
}



//*************************//
//*** Private functions ***//
//*************************//
//Making it easier to spy on and test this module
//I added an extra layer of abstraction to make it easier to modify (hopefully)
//Maybe I'll discover a better way to test the module, in which case I'll modify these Private functions
//while leaving the file's static functions alone.
PeriodicAlarmCallback TimeServicePrivate_GetCallback(PeriodicAlarm self)
{
  return getCallback(self);
}

int16_t TimeServicePrivate_GetPeriod(PeriodicAlarm self)
{
  return getPeriod(self);
}

void TimeServicePrivate_SetCounter(PeriodicAlarm self, int16_t value)
{
  setCounter(self, value);
}

int16_t TimeServicePrivate_GetCounter(PeriodicAlarm self)
{
  return getCounter(self);
}

void TimeServicePrivate_SetExecuteCallbackFlag(PeriodicAlarm self, BOOL executeCallbackNow)
{
  return setExecuteCallbackNowFlag(self, executeCallbackNow);
}

BOOL TimeServicePrivate_GetExecuteCallbackFlag(PeriodicAlarm self)
{
  return getExecuteCallbackNowFlag(self);
}
