#include "TimeService.h"
#include <avr/interrupt.h>
#include "ChipFunctions.h"
#include "LedNumber.h"



//****************************//
//*** File-scope functions ***//
//****************************//
LedNumber numericDisplay;


//Callbacks for TimeService
typedef struct
{
  LedNumber numericDisplay;
  int16_t displayValue;
} UpdateDisplayValueParams;
void updateDisplayValue(void * params)
{
  UpdateDisplayValueParams * self = (UpdateDisplayValueParams *)params;
  (self->displayValue)++;
  if (self->displayValue >= 10000)
  {
    self->displayValue = 0;
  }
  LedNumber_SetNumber(self->numericDisplay, self->displayValue);
}


//*******************//
//*** The program ***//
//*******************//
int main(void)
{
  PeriodicAlarm alarm_UpdateDisplayValue;
  PeriodicAlarmCallback callback_UpdateDisplayValue = &updateDisplayValue;
  int16_t displayValue = 0;
  UpdateDisplayValueParams updateDisplayValueParams;

  //Set up hardware
  TimeService_HwSetup();
  LedNumber_HwSetup();

  //Create interfaces
  TimeService_Create();
  numericDisplay = LedNumber_Create(LED_THOUSANDS);

  //Set up interfaces
  alarm_UpdateDisplayValue = TimeService_AddPeriodicAlarm(callback_UpdateDisplayValue, 1000);
  updateDisplayValueParams.numericDisplay = numericDisplay;
  updateDisplayValueParams.displayValue = displayValue;

  LedNumber_SetNumber(numericDisplay, 0);
  TimeService_ActivatePeriodicAlarm(alarm_UpdateDisplayValue);

  ChipFunctions_EnableGlobalInterrupts();

  while (1)
  {
    TimeService_ServiceSingleCallback(alarm_UpdateDisplayValue, (void *)&updateDisplayValueParams);
  }
}

//Interrupt handlers
ISR(TIMER0_COMPA_vect)
{
  TimeService_TimerTick();
  LedNumber_ShowNumber(numericDisplay);
}
