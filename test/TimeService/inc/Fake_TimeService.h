#ifndef Fake_TimeService_H_
#define Fake_TimeService_H_

#include "TimeService.h"

//Careful! At the moment this fake can only be used with a single PeriodicAlarm

void Fake_TimeService_Create(void);
void Fake_TimeService_Destroy(void);

int16_t Fake_TimeService_GetCounter(PeriodicAlarm self);
void Fake_TimeService_SetCounter(PeriodicAlarm self, int16_t value);

#endif
