extern "C"
{
  #include "Fake_TimeService.h"
  #include "TimeService.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_Fake_TimeService.h"

TEST_GROUP(Fake_TimeService)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(Fake_TimeService, WiringCheck)
{
  FAIL("Fake_TimeService wiring check");
}
