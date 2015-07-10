extern "C"
{
  #include "LedDigitWiring.h"
}

#include "Mock_LedDigitWiring.h"
#include "CppUTestExt/MockSupport.h"



//************************//
//*** Helper functions ***//
//************************//
void expectHwSetup(void)
{
  mock().expectOneCall("LedDigitWiring_HwSetup");
}

void expectPinCall(BOOL setPin, LedDigitWiring_Pin pin)
{
  if (setPin == TRUE)
  {
    mock().expectOneCall("LedDigitWiring_TurnSegmentOn")
          .withParameter("pin", pin);
  }
  else
  {
    mock().expectOneCall("LedDigitWiring_TurnSegmentOff")
          .withParameter("pin", pin);
  }
}

//TRUE to set a pin, FALSE to clear a pin
void expectPinCalls(BOOL pinA, BOOL pinB, BOOL pinC, BOOL pinD, BOOL pinE, BOOL pinF, BOOL pinG)
{
  expectPinCall(pinA, PIN_A);
  expectPinCall(pinB, PIN_B);
  expectPinCall(pinC, PIN_C);
  expectPinCall(pinD, PIN_D);
  expectPinCall(pinE, PIN_E);
  expectPinCall(pinF, PIN_F);
  expectPinCall(pinG, PIN_G);
}

void expectPinDecimalPointCall(BOOL pinDP)
{
  expectPinCall(pinDP, PIN_DP);
}



//**********************//
//*** Mock Functions ***//
//**********************//
void LedDigitWiring_HwSetup(void)
{
  mock().actualCall("LedDigitWiring_HwSetup");
}

void LedDigitWiring_TurnSegmentOn(LedDigitWiring_Pin pin)
{
  mock().actualCall("LedDigitWiring_TurnSegmentOn")
        .withParameter("pin", pin);
}

void LedDigitWiring_TurnSegmentOff(LedDigitWiring_Pin pin)
{
  mock().actualCall("LedDigitWiring_TurnSegmentOff")
        .withParameter("pin", pin);
}
