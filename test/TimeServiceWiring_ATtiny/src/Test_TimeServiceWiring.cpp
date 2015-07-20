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
  int8_t expected;

  void setup()
  {
    expected = 0;
    TCCR0A = 0;
    TCCR0B = 0;
    OCR0A = 0;
    TIMSK = 0;
  }

  void teardown()
  {
  }
};


//Can't test the order in which things occur witout much more effort. Oh well.
TEST(TimeServiceWiring, HardwareSetup)
{
  uint8_t expectedTCCR0A = 0;
  uint8_t expectedTCCR0B = 0;
  uint8_t expectedOCR0A = 0;
  uint8_t expectedTIMSK = 0;

  SHIFT_AND_SET_BITMASK_TO(expectedTCCR0A, TS_EIGHT_BIT, BITMASK_TS_TIMER_BIT_WIDTH);
  SHIFT_AND_SET_BITMASK_TO(expectedTCCR0A, TRUE, BITMASK_TS_CLEAR_TIMER_ON_MATCH);
  SHIFT_AND_SET_BITMASK_TO(expectedTCCR0B, TS_PRESCALE_FACTOR_8, BITMASK_TS_PRESCALE_FACTOR);
  expectedOCR0A = 125;
  SHIFT_AND_SET_BITMASK_TO(expectedTIMSK, TRUE, BITMASK_TS_COMPARE_INTERRUPT_0A);

  TimeServiceWiring_HwSetup();

  BYTES_EQUAL(expectedTCCR0A, TCCR0A);
  BYTES_EQUAL(expectedTCCR0B, TCCR0B);
  LONGS_EQUAL(expectedOCR0A, OCR0A);
  BYTES_EQUAL(expectedTIMSK, TIMSK);
}

TEST(TimeServiceWiring, MockRegistersClearedAfterSetup)
{
  LONGS_EQUAL(0, expected); //Haha
  LONGS_EQUAL(0, TCCR0A);
  LONGS_EQUAL(0, TCCR0B);
  LONGS_EQUAL(0, OCR0A);
  LONGS_EQUAL(0, TIMSK)
}

TEST(TimeServiceWiring, SetAllTimerBitWidthBits)
{
  SET_BITMASK_TO(expected, BITMASK_TS_TIMER_BIT_WIDTH, BITMASK_TS_TIMER_BIT_WIDTH);
  TimeServiceWiring_SetTimerBitWidth(TS_SIXTEEN_BIT);
  BYTES_EQUAL(expected, TCCR0A);
}

TEST(TimeServiceWiring, ClearAllTimerBitWidthBits)
{
  TCCR0A = 0xff;
  expected = 0xff;
  CLEAR_BITS(expected, BITMASK_TS_TIMER_BIT_WIDTH);

  TimeServiceWiring_SetTimerBitWidth(TS_EIGHT_BIT);

  BYTES_EQUAL(expected, TCCR0A);
}

TEST(TimeServiceWiring, SetAllTimerOnMatchBits)
{
  SET_BITS(expected, BITMASK_TS_CLEAR_TIMER_ON_MATCH);
  TimeServiceWiring_ClearTimerOnMatch(TRUE);
  BYTES_EQUAL(expected, TCCR0A);
}

TEST(TimeServiceWiring, ClearAllTimerOnMatchBits)
{
  TCCR0A = 0xff;
  expected = 0xff;
  CLEAR_BITS(expected, BITMASK_TS_CLEAR_TIMER_ON_MATCH);

  TimeServiceWiring_ClearTimerOnMatch(FALSE);

  BYTES_EQUAL(expected, TCCR0A);
}

TEST(TimeServiceWiring, SetAllPrescalerBits)
{
  SET_BITS(expected, BITMASK_TS_PRESCALE_FACTOR);
  TimeServiceWiring_SetPrescaleFactor(TS_EXTERNAL_T0_RISING);
  BYTES_EQUAL(expected, TCCR0B);
}

TEST(TimeServiceWiring, ClearAllPrescalerBits)
{
  TCCR0B = 0xff;
  expected = 0xff;
  CLEAR_BITS(expected, BITMASK_TS_PRESCALE_FACTOR);

  TimeServiceWiring_SetPrescaleFactor(TS_TIMER_STOPPED);

  BYTES_EQUAL(expected, TCCR0B);
}

TEST(TimeServiceWiring, SetMaxTimerCompareValue)
{
  TimeServiceWiring_SetTimerCompareValue0A(255);
  LONGS_EQUAL(OCR0A, 255);
}

TEST(TimeServiceWiring, SetMinTimerCompareValue)
{
  TimeServiceWiring_SetTimerCompareValue0A(0);
  LONGS_EQUAL(OCR0A, 0);
}

TEST(TimeServiceWiring, SetAllEnableTimerCompareInterruptBits)
{
  SET_BITS(expected, BITMASK_TS_COMPARE_INTERRUPT_0A);
  TimeServiceWiring_SetTimerCompareInterrupt0A(TRUE);
  BYTES_EQUAL(expected, TIMSK);
}

TEST(TimeServiceWiring, ClearAllEnableTimerCompareInterruptBits)
{
  TIMSK = 0xff;
  expected = 0xff;
  CLEAR_BITS(expected, BITMASK_TS_COMPARE_INTERRUPT_0A);

  TimeServiceWiring_SetTimerCompareInterrupt0A(FALSE);

  BYTES_EQUAL(expected, TIMSK);
}
