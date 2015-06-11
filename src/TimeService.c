#include "TimeService.h"
#include "DataTypes.h"

static PeriodicCallback callback;


static void clearCallback(void)
{
  callback = NULL;
}

void TimeService_Create(void)
{
  clearCallback();
}

void TimeService_Destroy(void)
{
  clearCallback();
}

void TimeService_SetPeriodicAlarm(PeriodicCallback callbackFunction)
{
  callback = callbackFunction;
}

PeriodicCallback TimeService_GetCallback(void)
{
  return callback;
}
