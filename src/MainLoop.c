#include "MainLoop.h"
#include "Adc.h"
#include "NumericFunctions.h"


static int8_t adcConversionStatus;


//*** File-scope functions ***//
static int8_t getConversionStatus(void)
{
  return adcConversionStatus;
}

static void setConversionStatus(int8_t status)
{
  adcConversionStatus = status;
}



//*** Public functions ***//
//Wrappers for interrupts
void MainLoop_AdcConversion(void * param)
{
  RETURN_IF_NULL(param);
  PeriodicAlarm * adcReadAlarmPointer = (PeriodicAlarm *)param;
  adcConversionStatus = Adc_StartConversion();
  TimeService_ActivatePeriodicAlarm(*adcReadAlarmPointer);
}

void MainLoop_GetReading(void * param)
{
  getReadingParameterStruct * parameterStruct;
  int8_t adcReturnCode;
  int16_t adcReading;
  float reading;

  RETURN_IF_NULL(param);
  parameterStruct = (getReadingParameterStruct *)param;
  RETURN_IF_NULL(parameterStruct->outputModel);
  RETURN_IF_NULL(parameterStruct->ledDisplay);
  RETURN_IF_NULL(parameterStruct->getReadingAlarm);

  if (getConversionStatus() == ADC_CONVERSION_BUSY)
  {
    return;
  }
  adcReturnCode = Adc_Read(&adcReading);
  if (adcReturnCode != ADC_READ_SUCCESS)
  {
    return;
  }
  reading = LineFit_GetOutput(parameterStruct->outputModel, adcReading);
  LedNumber_SetNumber(parameterStruct->ledDisplay, round_int16(reading));
  TimeService_DeactivatePeriodicAlarm(parameterStruct->getReadingAlarm);
}

void MainLoop_UpdateDisplay(void * param)
{
  LedNumber * ledDisplay;
  RETURN_IF_NULL(param);
  ledDisplay = (LedNumber *)param;

  LedNumber_ShowNumber(*ledDisplay);
}



//*** Private functions ***//
void MainLoop_Private_SetAdcConversionStatus(int8_t status)
{
  setConversionStatus(status);
}
