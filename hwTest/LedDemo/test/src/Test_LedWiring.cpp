extern "C"
{
  #include "LedWiring.h"
  #include <avr/io.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedWiring.h"


TEST_GROUP(LedWiring)
{
  void setup()
  {
    DDRA = 0;
    PORTA = 0;
  }

  void teardown()
  {
  }
};

TEST(LedWiring, CheckSetup)
{
  LONGS_EQUAL(0, DDRA);
  LONGS_EQUAL(0, PORTA);
}

TEST(LedWiring, Init)
{
  LedWiring_Init();
  LONGS_EQUAL(0xff, DDRA);
  LONGS_EQUAL(0, PORTA);
}

TEST(LedWiring, SetLowestLed)
{
  LedWiring_Init();
  LedWiring_SetLed(LED_1);
  LONGS_EQUAL(0x01, PORTA);
}

TEST(LedWiring, SetHighestLed)
{
  LedWiring_Init();
  LedWiring_SetLed(LED_8);
  LONGS_EQUAL(0x80, PORTA);
}

TEST(LedWiring, ClearLowestLed)
{
  LedWiring_Init();
  LedWiring_SetLed(LED_1);
  LedWiring_ClearLed(LED_1);
  LONGS_EQUAL(0x00, PORTA);
}
