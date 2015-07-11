extern "C"
{
  #include "TimeServiceWiring.h"
}
#include "CppUTestExt/MockSupport.h"

void TimeServiceWiring_HwSetup(void)
{
  mock().actualCall("TimeServiceWiring_HwSetup");
}
