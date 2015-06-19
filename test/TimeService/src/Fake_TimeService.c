#include "Fake_TimeService.h"
#include "TimeService.h"

static int16_t fakeCounter;

void Fake_TimeService_Create(void)
{
  fakeCounter = PA_UNUSED;
}

void Fake_TimeService_Destroy(void)
{
}

int16_t Fake_TimeService_GetCounter(PeriodicAlarm self)
{
  return fakeCounter;
}

void Fake_TimeService_SetCounter(PeriodicAlarm self, int16_t value)
{
  fakeCounter = value;
}
