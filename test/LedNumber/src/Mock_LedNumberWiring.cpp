extern "C"
{
  #include "LedNumberWiring.h"
}

#include "CppUTestExt/MockSupport.h"
#include "Mock_LedNumberWiring.h"



//************************//
//*** Helper Functions ***//
//************************//
void expectSetSelectPin(LedNumberWiring_Place led_number)
{
  mock().expectOneCall("LedNumberWiring_SetSelectPin")
        .withParameter("pin", led_number);
}



//**********************//
//*** Mock Functions ***//
//**********************//
void LedNumberWiring_HwSetup(void)
{
  mock().actualCall("LedNumberWiring_HwSetup");
}

void LedNumberWiring_SetSelectPin(LedNumberWiring_Place pin)
{
  mock().actualCall("LedNumberWiring_SetSelectPin")
        .withParameter("pin", pin);
}
