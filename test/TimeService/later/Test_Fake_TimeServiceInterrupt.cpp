extern "C"
{
  #include "Fake_TimeServiceInterrupt.h"
  #include "TimeServiceInterrupt.h"
  #include "TimeService.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_Fake_TimeServiceInterrupt.h"

TEST_GROUP(Fake_TimeServiceInterrupt)
{
  void setup()
  {
    PeriodicAlarm alarm;
    //Hmmm, we're going to have to work on scoping issues
    TimeService_Create();
    alarm = TimeService_AddPeriodicAlarm();

  }

  void teardown()
  {
    TimeService_Destroy();
  }
};

TEST(Fake_TimeServiceInterrupt, CounterZeroAfterCreate)
{
  LONGS_EQUAL(0, TimeServiceInterrupt_GetCounter());
}
