#ifndef TimeService_H_
#define TimeService_H_

#include "DataTypes.h"



//******************//
//*** Data Types ***//
//******************//
typedef struct PeriodicAlarmStruct * PeriodicAlarm;

#define MAX_PERIODIC_ALARMS 10

//Define the function pointer type for callback functions.
//Compiler magic!
typedef void (*PeriodicAlarmCallback)(void *);



//***********************//
//*** Public Functions **//
//***********************//
//Initialize the hardware timer.
void TimeService_HwSetup(void);

//Creates and initializes the TimeService as a whole.
//No alarms are created; they must be added individually by the user.
void TimeService_Create(void);

//Resets the time service as a whole, destroying all alarms.
//It is the user's responsibility to discard all PeriodicAlarm pointers
//after the TimeService is destroyed,
//although the program shouldn't crash if you do.
void TimeService_Destroy(void);

//Creates and returns a pointer to a new periodic alarm.
//This alarm will not trigger until it is activated.
PeriodicAlarm TimeService_AddPeriodicAlarm(PeriodicAlarmCallback callback, int16_t period, BOOL executeInIsr);

//Removes the given alarm from the TimeService.
//The pointer to the alarm will be set to NULL.
void TimeService_RemovePeriodicAlarm(PeriodicAlarm self);

//Start the given alarm's timer.
void TimeService_ActivatePeriodicAlarm(PeriodicAlarm self);

//Stop the given alarm's timer.
void TimeService_DeactivatePeriodicAlarm(PeriodicAlarm self);

//Execute the alarm's callback functions if its period has expired.
//This function should NOT be called from within an interrupt routine
//because there is no guarantee that callbacks will execute quickly.
//Instead, it should be executed from within a task or the main loop.
//The void pointer will will be passed as arguments to the callback.
//A NULL pointer can be passed if no arguments are needed.
void TimeService_ServiceSingleCallback(PeriodicAlarm self, void * params);

//Increment and check alarm timers.
//This function is designed to be executed from within an interrupt routine.
//It should be called once per millisecond.
//It sets a flag that for each alarm to be serviced.
void TimeService_TimerTick(void);



#include "TimeServicePrivate.h"

#endif
