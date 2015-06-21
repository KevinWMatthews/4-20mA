#include "MainLoop.h"
#include "TimeService.h"
#include "AtoD.h"

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
int8_t MainLoop_GetAtodConversionStatus(void)
{
  return atodConversionStatus;
}

void MainLoop_AtodConversion(void)
{
  atodConversionStatus = AtoD_StartConversion();
}

void MainLoop_ReadAtodValue(int16_t * atodValue)
{
  int8_t readResult;
  if (getConversionStatus() == ATOD_CONVERSION_BUSY)
  {
    return;
  }
  readResult = AtoD_Read(atodValue);
}


//*** Private functions ***//
void MainLoop_Private_SetAtodConversionStatus(int8_t status)
{
  setConversionStatus(status);
}
