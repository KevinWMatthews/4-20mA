#include "TimeService.h"
#include <avr/interrupt.h>
#include "ChipFunctions.h"
#include "LedNumber.h"



//****************************//
//*** File-scope functions ***//
//****************************//
//Callbacks for TimeService
void updateDisplay(void * params)
{
  LedNumber self = (LedNumber)params;
  LedNumber_ShowNumber(self);
}


//*******************//
//*** The program ***//
//*******************//
int main(void)
{
  PeriodicAlarm alarm_UpdateDisplay = NULL;
  PeriodicAlarmCallback callback_UpdateDisplay = &updateDisplay;
  LedNumber numericDisplay;

  //Set up hardware
  TimeService_HwSetup();
  LedNumber_HwSetup();

  //Create interfaces
  TimeService_Create();
  numericDisplay = LedNumber_Create(LED_THOUSANDS);

  //Set up interfaces
  alarm_UpdateDisplay = TimeService_AddPeriodicAlarm(callback_UpdateDisplay, 2);
  LedNumber_SetNumber(numericDisplay, 0);
  TimeService_ActivatePeriodicAlarm(alarm_UpdateDisplay);

  ChipFunctions_EnableGlobalInterrupts();

  while (1)
  {
    TimeService_ServiceSingleCallback(alarm_UpdateDisplay, (void *)numericDisplay);
  }
}

//Interrupt handlers
ISR(TIMER1_COMPA_vect)
{
  TimeService_TimerTick();
}
