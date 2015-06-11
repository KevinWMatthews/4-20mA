#ifndef TimeService_H_
#define TimeService_H_

//Define a function pointer type.
//Compiler magic!
typedef void (*PeriodicCallback)(void);

void TimeService_Create(void);
void TimeService_Destroy(void);

void TimeService_SetPeriodicAlarm(PeriodicCallback callbackFunction);
PeriodicCallback TimeService_GetCallback(void);

#endif
