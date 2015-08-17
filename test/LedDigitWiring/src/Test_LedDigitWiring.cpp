extern "C"
{
  #include "LedDigitWiring.h"
  #include <avr/io.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedDigitWiring.h"



TEST_GROUP(LedDigitWiring)
{
  void setup()
  {
    DDRB = 0;
    PORTB = 0;
    LedDigitWiring_HwSetup();
  }

  void teardown()
  {
  }

  //Memory registers are defined or mocked in avr/io.h
  void checkMemoryRegisters(uint8_t ddr, uint8_t port)
  {
    LONGS_EQUAL(ddr, DDRB);;
    LONGS_EQUAL(port, PORTB);
  }
};



//*******************//
//*** Unit Tests! ***//
//*******************//
TEST(LedDigitWiring, HwSetup)
{
  //Set GPIO to outputs, pull high to turn off LED digit segments
  checkMemoryRegisters(0xff, 0xff);
}

TEST(LedDigitWiring, SetSegmentA)
{
  LedDigitWiring_TurnSegmentOn(PIN_A);
  checkMemoryRegisters(0xff, 0xfe);
}

TEST(LedDigitWiring, ClearSegmentA)
{
  LedDigitWiring_TurnSegmentOn(PIN_A);
  LedDigitWiring_TurnSegmentOff(PIN_A);
  checkMemoryRegisters(0xff, 0xff);
}

TEST(LedDigitWiring, SetSegmentB)
{
  LedDigitWiring_TurnSegmentOn(PIN_B);
  checkMemoryRegisters(0xff, 0xfd);
}

TEST(LedDigitWiring, SetSegmentC)
{
  LedDigitWiring_TurnSegmentOn(PIN_C);
  checkMemoryRegisters(0xff, 0xfb);
}

TEST(LedDigitWiring, SetSegmentD)
{
  LedDigitWiring_TurnSegmentOn(PIN_D);
  checkMemoryRegisters(0xff, 0xf7);
}

TEST(LedDigitWiring, SetSegmentE)
{
  LedDigitWiring_TurnSegmentOn(PIN_E);
  checkMemoryRegisters(0xff, 0xef);
}

TEST(LedDigitWiring, SetSegmentF)
{
  LedDigitWiring_TurnSegmentOn(PIN_F);
  checkMemoryRegisters(0xff, 0xdf);
}

TEST(LedDigitWiring, SetSegmentG)
{
  LedDigitWiring_TurnSegmentOn(PIN_G);
  checkMemoryRegisters(0xff, 0xbf);
}

TEST(LedDigitWiring, SetSegmentDecimalPoint)
{
  LedDigitWiring_TurnSegmentOn(PIN_DP);
  checkMemoryRegisters(0xff, 0x7f);
}
