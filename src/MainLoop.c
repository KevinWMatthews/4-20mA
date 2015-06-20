#include "MainLoop.h"
#include "TimeService.h"
#include "AtoD.h"

static int8_t AtodConverstionStatus;

int8_t MainLoop_GetAtodConverstionStatus(void)
{
  return AtodConverstionStatus;
}

void MainLoop_AtodConversion(void)
{
  AtodConverstionStatus = AtoD_StartConversion();
}
