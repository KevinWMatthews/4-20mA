extern "C"
{
  #include "LedNumber.h"    //Code under test
  #include "Spy_LedDigit.h"
  #include "DataTypes.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedNumber.h"

static int8_t onesSelect;

TEST_GROUP(LedNumber)
{
  void setup()
  {
    onesSelect = PIN_UNDEFINED;
    LedNumber_Create(&onesSelect);
  }

  void teardown()
  {
    LedNumber_Destroy();
  }
};

TEST(LedNumber, CreateAndDestroy)
{
  //TODO learn how to detect a memory leak!
}

TEST(LedNumber, NoLedSelectedAfterInit)
{
  LONGS_EQUAL(onesSelect, PIN_OFF);
}

TEST(LedNumber, ShowSingleDigitNumber)
{
  LedNumber_ShowNumber(7);
  LONGS_EQUAL(PIN_ON, onesSelect);
  LONGS_EQUAL(SEVEN, LedDigitSpy_GetDigit());
}
