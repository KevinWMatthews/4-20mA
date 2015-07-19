#include "TimeService.h"
#include "LedNumber.h"
#include "Adc.h"
#include <avr/interrupt.h>
#include "ChipFunctions.h"



//******************//
//*** Data Types ***//
//******************//
typedef struct StartAdcReadParams
{
  PeriodicAlarm adcReadAlarm;
  int8_t adcStatus;
} StartAdcReadParams;

typedef struct ReadAdcParams
{
  PeriodicAlarm adcReadAlarm;
  int16_t adcReading;
} ReadAdcParams;



//****************************//
//*** File-scope functions ***//
//****************************//
//Callbacks for TimeService
void updateDisplay(void * params)
{
  LedNumber self = (LedNumber)params;
  LedNumber_ShowNumber(self);
}

void startAdcRead(void * params)
{
  StartAdcReadParams * self = (StartAdcReadParams *)params;

  self->adcStatus = Adc_StartConversion();
  TimeService_ActivatePeriodicAlarm(self->adcReadAlarm);
}

void readAdc(void * params)
{
  ReadAdcParams * self = (ReadAdcParams *)params;
  int16_t reading;

  if (Adc_Read(&reading) == ADC_READ_SUCCESS)
  {
    self->adcReading = reading;
    TimeService_DeactivatePeriodicAlarm(self->adcReadAlarm);
  }
}


//*** The program ***//
int main(void)
{
  PeriodicAlarm alarm_UpdateDisplay = NULL;
  PeriodicAlarm alarm_StartAdcRead = NULL;
  PeriodicAlarm alarm_AdcRead = NULL;
  PeriodicAlarmCallback callback_UpdateDisplay = &updateDisplay;
  PeriodicAlarmCallback callback_StartAdcRead = &startAdcRead;
  PeriodicAlarmCallback callback_ReadAdc = &readAdc;
  int16_t adcReading = 0;
  StartAdcReadParams startAdcReadParams = {alarm_AdcRead, ADC_INACTIVE};
  ReadAdcParams readAdcParams = {alarm_AdcRead, adcReading};
  LedNumber numericDisplay;


  //Set up hardware
  Adc_HwSetup();
  TimeService_HwSetup();
  LedNumber_HwSetup();

  //Create interfaces
  TimeService_Create();
  numericDisplay = LedNumber_Create(LED_THOUSANDS);

  //Set up interfaces
  alarm_UpdateDisplay = TimeService_AddPeriodicAlarm(callback_UpdateDisplay, 2, FALSE);
  alarm_StartAdcRead = TimeService_AddPeriodicAlarm(callback_StartAdcRead, 1000, FALSE);
  alarm_AdcRead = TimeService_AddPeriodicAlarm(callback_ReadAdc, 25, FALSE);
  LedNumber_SetNumber(numericDisplay, 0);
  TimeService_ActivatePeriodicAlarm(alarm_UpdateDisplay);
  TimeService_ActivatePeriodicAlarm(alarm_StartAdcRead);

  ChipFunctions_EnableGlobalInterrupts();

  while (1)
  {
    TimeService_ServiceSingleCallback(alarm_UpdateDisplay, (void *)numericDisplay);
    TimeService_ServiceSingleCallback(alarm_StartAdcRead, (void *)&startAdcReadParams);
    TimeService_ServiceSingleCallback(alarm_AdcRead, (void *)&readAdcParams);
  }
}

//Interrupt handlers
ISR(TIMER1_CMPA_vect)
{
  TimeService_TimerTick();
}
