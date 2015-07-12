extern "C"
{
  #include "TimeServiceWiringHw.h"
  #include <avr/io.h>
  #include "BitManip.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_TimeServiceWiringHw.h"

TEST_GROUP(TimeServiceWiringHw)
{
  void setup()
  {
    TCCR1B = 0;
    OCR1C = 0;
    TIMSK = 0;
  }

  void teardown()
  {
  }
};

TEST(TimeServiceWiringHw, MockRegistersClearedAfterSetup)
{
  LONGS_EQUAL(0, TCCR1B);
  LONGS_EQUAL(0, OCR1C);
  LONGS_EQUAL(0, TIMSK);
}

TEST(TimeServiceWiringHw, SetPrescaler_OtherBitsNotSet)
{
  TimeServiceWiringHw_SetPrescaler(TS_PRESCALE_FACTOR_64);
  CHECK_TRUE(IF_BITMASK(0x07, TCCR1B, 0xff));
}

TEST(TimeServiceWiringHw, SetPrescaler_OtherBitsNotCleared)
{
  TCCR1B = 0xff;
  TimeServiceWiringHw_SetPrescaler(TS_TIMER_STOPPED);
  CHECK_TRUE(IF_BITMASK(0xf0, TCCR1B, 0xff));
}

TEST(TimeServiceWiringHw, SetTimerCompare)
{
  TimeServiceWiringHw_SetTimerCompare(125);
  LONGS_EQUAL(OCR1C, 125);
}

TEST(TimeServiceWiringHw, SetClearTimerOnMatchFlag_OtherBitsNotSet)
{
  TimeServiceWiringHw_ClearTimerOnMatch(TRUE);
  CHECK_TRUE(IF_BITMASK(1<<CTC1, TCCR1B, 0xff));
}

TEST(TimeServiceWiringHw, SetClearTimerOnMatchFlag_OtherBitsNotCleared)
{
  TCCR1B = 0xff;
  TimeServiceWiringHw_ClearTimerOnMatch(FALSE);
  CHECK_TRUE(IF_BITMASK(0xff & ~(1<<CTC1), TCCR1B, 0xff));
}

TEST(TimeServiceWiringHw, EnableTimerCompareInterrupt_OtherBitsNotSet)
{
  TimeServiceWiringHw_SetTimerCompareInterrupt(TRUE);
  BYTES_EQUAL(1<<OCIE1A, TIMSK);
}

TEST(TimeServiceWiringHw, EnableTimerCompareInterrupt_OtherBitsNotCleared)
{
  TIMSK = 0xff;
  TimeServiceWiringHw_SetTimerCompareInterrupt(FALSE);
  BYTES_EQUAL(0xff & ~(1<<OCIE1A), TIMSK);
}
