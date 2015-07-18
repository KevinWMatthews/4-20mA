extern "C"
{
  #include "TimeServiceWiring.h"
}
#include "CppUTestExt/MockSupport.h"

void TimeServiceWiring_HardwareSetup(void)
{
  mock().actualCall("TimeServiceWiring_HardwareSetup");
}
