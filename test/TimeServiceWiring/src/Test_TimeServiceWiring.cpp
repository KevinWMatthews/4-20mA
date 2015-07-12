extern "C"
{
  #include "TimeServiceWiring.h"
  #include <avr/io.h>
  #include "BitManip.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_TimeServiceWiring.h"

TEST_GROUP(TimeServiceWiring)
{
  void setup()
  {
    TCCR1B = 0;
    OCR1C = 0;
  }

  void teardown()
  {
  }
};

TEST(TimeServiceWiring, MockRegistersClearedAfterSetup)
{
  LONGS_EQUAL(0, TCCR1B);
  LONGS_EQUAL(0, OCR1C);
}

TEST(TimeServiceWiring, SetPrescaler_OtherBitsNotSet)
{
  TimeServiceWiringPrivate_SetPrescaler(TS_PRESCALE_FACTOR_64);
  CHECK_TRUE(IFBITMASK(0x07, TCCR1B, 0xff));
}

TEST(TimeServiceWiring, SetPrescaler_OtherBitsNotCleared)
{
  TCCR1B = 0xff;
  TimeServiceWiringPrivate_SetPrescaler(TS_TIMER_STOPPED);
  CHECK_TRUE(IFBITMASK(0xf0, TCCR1B, 0xff));
}

TEST(TimeServiceWiring, SetTimerCompare)
{
  TimeServiceWiringPrivate_SetTimerCompare(125);
  LONGS_EQUAL(OCR1C, 125);
}

TEST(TimeServiceWiring, SetClearTimerOnMatchFlag_OtherBitsNotSet)
{
  TimeServiceWiringPrivate_ClearTimerOnMatch(TRUE);
  CHECK_TRUE(IFBITMASK(1<<CTC1, TCCR1B, 0xff));
}

TEST(TimeServiceWiring, SetClearTimerOnMatchFlag_OtherBitsNotCleared)
{
  TCCR1B = 0xff;
  TimeServiceWiringPrivate_ClearTimerOnMatch(FALSE);
  CHECK_TRUE(IFBITMASK(0xff & ~(1<<CTC1), TCCR1B, 0xff));
}
