extern "C"
{
  #include "AdcWiring.h"
}

#include "CppUTestExt/MockSupport.h"



//**********************//
//*** Mock Functions ***//
//**********************//
void AdcWiring_HwSetup(void)
{
  mock().actualCall("AdcWiring_HwSetup");
}

void AdcWiring_Enable(void)
{
  mock().actualCall("AdcWiring_Enable");
}

void AdcWiring_FirstConversion(void)
{
  mock().actualCall("AdcWiring_FirstConversion");
}

BOOL AdcWiring_IsAdcBusy(void)
{
  mock().actualCall("AdcWiring_IsAdcBusy");
  return (BOOL)(mock().intReturnValue());
}

void AdcWiring_StartConversion(void)
{
  mock().actualCall("AdcWiring_StartConversion");
}

BOOL AdcWiring_IsInterruptFlagSet(void)
{
  mock().actualCall("AdcWiring_IsInterruptFlagSet");
  return (BOOL)(mock().intReturnValue());
}

uint8_t AdcWiring_ReadDataRegister_High(void)
{
  mock().actualCall("AdcWiring_ReadDataRegister_High");
  return mock().intReturnValue();
}

uint8_t AdcWiring_ReadDataRegister_Low(void)
{
  mock().actualCall("AdcWiring_ReadDataRegister_Low");
  return mock().intReturnValue();
}

void AdcWiring_ClearInterruptFlag(void)
{
  mock().actualCall("AdcWiring_ClearInterruptFlag");
}
