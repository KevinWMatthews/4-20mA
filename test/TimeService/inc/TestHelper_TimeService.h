#ifndef TestHelper_TimeService_H
#define TestHelper_TimeService_H

//Mock callbacks
void callbackFunction(void * params);
void callbackFunction2(void * params);
void callbackFunction3(void * params);

//Condition checks
void checkCounterAndFlag(PeriodicAlarm self, int16_t counter, BOOL executeNow);
void checkCallbackAndPeriod(PeriodicAlarm alarm, PeriodicAlarmCallback callbackFunction, int16_t alarmPeriod);

#endif
