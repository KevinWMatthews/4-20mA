#include "MainLoop.h"
#include "AtoD.h"
#include "NumericFunctions.h"


static int8_t atodConversionStatus;


//*** File-scope functions ***//
static int8_t getConversionStatus(void)
{
  return atodConversionStatus;
}

static void setConversionStatus(int8_t status)
{
  atodConversionStatus = status;
}



//*** Public functions ***//
//Wrappers for interrupts
void MainLoop_AtodConversion(void * param)
{
  RETURN_IF_NULL(param);
  PeriodicAlarm * atodReadAlarmPointer = (PeriodicAlarm *)param;
  atodConversionStatus = AtoD_StartConversion();
  TimeService_ActivatePeriodicAlarm(*atodReadAlarmPointer);
}

void MainLoop_GetReading(void * param)
{
  getReadingParameterStruct * parameterStruct;
  int8_t atodReturnCode;
  int16_t atodReading;
  float reading;

  RETURN_IF_NULL(param);
  parameterStruct = (getReadingParameterStruct *)param;
  RETURN_IF_NULL(parameterStruct->outputModel);
  RETURN_IF_NULL(parameterStruct->ledDisplay);
  RETURN_IF_NULL(parameterStruct->getReadingAlarm);

  if (getConversionStatus() == ATOD_CONVERSION_BUSY)
  {
    return;
  }
  atodReturnCode = AtoD_Read(&atodReading);
  if (atodReturnCode != ATOD_READ_SUCCESS)
  {
    return;
  }
  reading = LineFit_GetOutput(parameterStruct->outputModel, atodReading);
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
void MainLoop_Private_SetAtodConversionStatus(int8_t status)
{
  setConversionStatus(status);
}
