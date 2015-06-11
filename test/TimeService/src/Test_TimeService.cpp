extern "C"
{
  #include "TimeService.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_TimeService.h"

TEST_GROUP(TimeService)
{
  void setup()
  {
    TimeService_Create();
  }

  void teardown()
  {
    TimeService_Destroy();
  }
};

TEST(TimeService, Create)
{
  POINTERS_EQUAL(NULL, TimeService_GetCallback());
}

TEST(TimeService, DestroySupportsMultipleCalls)
{
  TimeService_Destroy();
}

TEST(TimeService, CallbackClearedAfterDestroy)
{
  PeriodicCallback callback;

  TimeService_SetPeriodicAlarm(callback);
  TimeService_Destroy();
  POINTERS_EQUAL(NULL, TimeService_GetCallback());
}

TEST(TimeService, SetCallbackFunction)
{
  PeriodicCallback callback;

  TimeService_SetPeriodicAlarm(callback);
  POINTERS_EQUAL(callback, TimeService_GetCallback());
}
