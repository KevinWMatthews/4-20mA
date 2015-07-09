extern "C"
{
  #include "LedDigit.h"
}

#include "CppUTestExt/MockSupport.h"
#include "Mock_LedDigit.h"



int8_t dummyDigit;  //Used to prevent null pointer checks from failing



//************************//
//*** Helper Functions ***//
//************************//
void expectSetDigit(LedDigit_Value value)
{
  mock().expectOneCall("LedDigit_SetDigit")
        .withParameter("self", &dummyDigit)
        .withParameter("value", value);
}

void expectShowDigit(void)
{
  mock().expectOneCall("LedDigit_UpdateLed")
        .withParameter("self", &dummyDigit);
}

void expectTurnOffDigit(void)
{
  mock().expectOneCall("LedDigit_TurnLedOff")
        .withParameter("self", &dummyDigit);
}



//**********************//
//*** Mock Functions ***//
//**********************//
void LedDigit_HwSetup(void)
{
  mock().actualCall("LedDigit_HwSetup");
}

LedDigit LedDigit_Create(void)
{
  return (LedDigit)&dummyDigit;   //This prevents null pointer checks from failing
}

void LedDigit_Destroy(LedDigit * self)
{
}

void LedDigit_SetDigit(LedDigit self, LedDigit_Value value)
{
  mock().actualCall("LedDigit_SetDigit")
        .withParameter("self", self)
        .withParameter("value", value);
}

void LedDigit_ClearDigit(LedDigit self)
{
  mock().actualCall("LedDigit_ClearDigit")
        .withParameter("self", self);
}

void LedDigit_UpdateLed(LedDigit self)
{
    mock().actualCall("LedDigit_UpdateLed")
          .withParameter("self", self);
}

void LedDigit_TurnLedOff(LedDigit self)
{
  mock().actualCall("LedDigit_TurnLedOff")
        .withParameter("self", self);
}

void LedDigit_ClearDecimal(LedDigit self)
{
  mock().actualCall("LedDigit_ClearDecimal")
        .withParameter("self", self);
}

void LedDigit_ClearAll(LedDigit self)
{
  mock().actualCall("LedDigit_ClearAll")
        .withParameter("self", self);
}

LedDigit_Value LedDigit_CurrentDigit(LedDigit self)
{
  mock().actualCall("LedDigit_CurrentDigit")
        .withParameter("self", self);
  return (LedDigit_Value)(mock().intReturnValue());
}

BOOL LedDigit_IsDecimalShown(LedDigit self)
{
  mock().actualCall("LedDigit_IsDecimalShown")
        .withParameter("self", self);
  return (BOOL)(mock().intReturnValue());
}
