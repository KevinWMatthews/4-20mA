extern "C"
{
  #include "DataTypes.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_DataTypes.h"

//This is the way that AVR defines pins
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

TEST_GROUP(DataTypes)
{
  Pin pin;
  uint8_t memoryRegister;

  void setup()
  {
    pin = Pin_Create(&memoryRegister, (1<<PIN0));
  }

  void teardown()
  {
    Pin_Destroy(&pin);
  }
};

TEST(DataTypes, CreatePin)
{
  POINTERS_EQUAL(&memoryRegister, Pin_GetAddress(pin));
  LONGS_EQUAL(1<<PIN0, Pin_GetBitmask(pin));
  LONGS_EQUAL(PIN_UNDEFINED, Pin_GetState(pin));
}

TEST(DataTypes, DestroyCanHandlesNullPointer)
{
  Pin_Destroy(&pin);
}

TEST(DataTypes, AllFunctionsCanHandleNull)
{
  POINTERS_EQUAL(NULL, Pin_GetAddress(NULL));
  LONGS_EQUAL(NULL_POINTER, Pin_GetBitmask(NULL));
  LONGS_EQUAL(PIN_NULL_POINTER, Pin_GetState(NULL));
  Pin_SetState(NULL, PIN_UNDEFINED);
}

TEST(DataTypes, SetPinStateHigh)
{
  Pin_SetState(pin, PIN_HIGH);
  LONGS_EQUAL(PIN_HIGH, Pin_GetState(pin));
  LONGS_EQUAL(PIN_HIGH, memoryRegister);
}

TEST(DataTypes, SetPinStateLow)
{
  Pin_SetState(pin, PIN_HIGH);
  Pin_SetState(pin, PIN_LOW);
  LONGS_EQUAL(PIN_LOW, Pin_GetState(pin));
  LONGS_EQUAL(PIN_LOW, memoryRegister);
}
