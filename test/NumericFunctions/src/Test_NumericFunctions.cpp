extern "C"
{
  #include "NumericFunctions.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_NumericFunctions.h"

TEST_GROUP(NumericFunctions)
{
  void setup()
  {
  }

  void teardown()
  {
  }
};

TEST(NumericFunctions, PositiveNumberRoundingUp)
{
  LONGS_EQUAL(5, round_int16(4.5));
}

TEST(NumericFunctions, PositiveNumberRoundingDown)
{
  LONGS_EQUAL(4, round_int16(4.4));
}


TEST(NumericFunctions, NegativeNumberRoundingUp)
{
  LONGS_EQUAL(-5, round_int16(-4.5));
}

TEST(NumericFunctions, NegativeNumberRoundingDown)
{
  LONGS_EQUAL(-4, round_int16(-4.4));
}
