#ifndef TestHelper_TimeService_H
#define TestHelper_TimeService_H



//This file facilitates specific test cases.
//It can use some reorganization



//Sample callback parameter data type
typedef struct callbackParameter
{
  int anInteger;
  float aFloat;
} callbackParameter;



//Public variables
extern callbackParameter structCallbackParameter;
extern int integerCallbackParameter;



//Sample callbacks
void doubleIntegerParamemeter(void * params);
void useStructParameter(void * params);



//Mock callbacks
void callbackFunction(void * params);
void callbackFunction2(void * params);
void callbackFunction3(void * params);



//Condition checks
void checkCounterAndFlag(PeriodicAlarm self, int16_t counter, BOOL executeNow);
void checkCallbackAndPeriod(PeriodicAlarm alarm, PeriodicAlarmCallback callbackFunction, int16_t alarmPeriod);



#endif
