#include "MainLoop.h"
#include "AtoD.h"


static int8_t atodConversionStatus;
static PeriodicAlarm atodReadAlarm;
static LedNumber ledDisplay;
static LineFit outputModel;


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
void MainLoop_Init(PeriodicAlarm atodRead, LedNumber number, LineFit line)
{
  atodReadAlarm = atodRead;
  ledDisplay = number;
  outputModel = line;
}

//Wrappers for interrupts
void MainLoop_AtodConversion(void)
{
  atodConversionStatus = AtoD_StartConversion();
  TimeService_ActivatePeriodicAlarm(atodReadAlarm);
}


void MainLoop_UpdateDisplay(void)
{
  LedNumber_ShowNumber(ledDisplay);
}


void MainLoop_GetReading(void)
{
  int8_t atodReturnCode;
  int16_t atodReading;
  float reading;

  if (getConversionStatus() == ATOD_CONVERSION_BUSY)
  {
    return;
  }
  atodReturnCode = AtoD_Read(&atodReading);
  if (atodReturnCode != ATOD_READ_SUCCESS)
  {
    return;
  }
  reading = LineFit_GetOutput(outputModel, atodReading);
    //TODO round reading
  LedNumber_SetNumber(ledDisplay, (int16_t)(reading));
  TimeService_DeactivatePeriodicAlarm(atodReadAlarm);
}


//*** Private functions ***//
void MainLoop_Private_SetAtodConversionStatus(int8_t status)
{
  setConversionStatus(status);
}
