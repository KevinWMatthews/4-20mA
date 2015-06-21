#include "MainLoop.h"
#include "TimeService.h"
#include "AtoD.h"

static int8_t atodConversionStatus;
static LedNumber number;

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
void MainLoop_Init(LedNumber ledDisplay)
{
  number = ledDisplay;
}

//Wrappers for interrupts
void MainLoop_AtodConversion(void)
{
  atodConversionStatus = AtoD_StartConversion();
}


void MainLoop_UpdateDisplay(void)
{
  LedNumber_ShowNumber(number);
}


//We probably don't want all of this in one function
void MainLoop_GetReading(LedNumber ledDisplay, LineFit outputModel)
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
}

int8_t MainLoop_GetAtodConversionStatus(void)
{
  return atodConversionStatus;
}


//*** Private functions ***//
void MainLoop_Private_SetAtodConversionStatus(int8_t status)
{
  setConversionStatus(status);
}
