extern "C"
{
  #include "LedNumber.h"    //Code under test
  #include "DataTypes.h"
  #include <string.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_LedNumber.h"

#define NUMBER_OF_DIGITS 1

typedef enum
{
  //Pins 3 and 8 are not available for use
  PIN1 = 0,
  PIN2 = 1,
  PIN4 = 2,
  PIN5 = 3,
  PIN6 = 4,
  PIN7 = 5,
  PIN9 = 6,
  PIN10 = 7,
  PIN_MAX = 8
} VirtualPin_PinNumber;

int8_t virtualPins[PIN_MAX];


TEST_GROUP(LedNumber)
{
  LedNumber number;
  LedDigit_DataPins dataPins;

  void setup()
  {
    memset(virtualPins, PIN_UNDEFINED, PIN_MAX);
    wireVirtualPins();
    number = LedNumber_Create(&dataPins, NUMBER_OF_DIGITS);
  }

  void teardown()
  {
    LedNumber_Destroy(&number);
  }

  void wireVirtualPins(void)
  {
    dataPins.pin1 = &virtualPins[0];
    dataPins.pin2 = &virtualPins[1];
    dataPins.pin4 = &virtualPins[2];
    dataPins.pin5 = &virtualPins[3];
    dataPins.pin6 = &virtualPins[4];
    dataPins.pin7 = &virtualPins[5];
    dataPins.pin9 = &virtualPins[6];
    dataPins.pin10 = &virtualPins[7];
  }

  void checkStateOfAllPins(Pin state)
  {
    for (int i = 0; i < PIN_MAX; i++)
    {
      LONGS_EQUAL(state, virtualPins[i]);
    }
  }
};

TEST(LedNumber, Create)
{
  //TODO learn how to detect a memory leak!
  checkStateOfAllPins(PIN_UNDEFINED);
}

TEST(LedNumber, Destroy)
{
  checkStateOfAllPins(PIN_UNDEFINED);
}

// TEST(LedNumber, ShowSingleDigitNumber)
// {
//   LedNumber_Show(7);
//   LONGS_EQUAL(SEVEN, SpyDeadDrop);
//   LONGS_EQUAL(PIN_ON, SelectPinForLed1);
// }
