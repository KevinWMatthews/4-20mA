extern "C"
{
  #include "LedNumber.h"
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

TEST(LedNumber, NoLedSelectedAfterInit)
{
  LONGS_EQUAL(onesSelect, PIN_OFF);
}

// TEST(LedNumber, ShowSingleDigitNumber)
// {
//   LedNumber_ShowNumber(number, 7);
//   TEST(PIN_ON, HwSelect_Led1);
//   TEST(LedDigitSpy_GetDigit, SEVEN);
// }
