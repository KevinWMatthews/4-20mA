extern "C"
{
  #include "LedNumber.h"    //Code under test
  #include "LedDigit.h"
  #include "LedNumberWiring.h"
  #include <math.h>
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_LedNumber.h"
#include "Mock_LedDigit.h"
#include "Mock_LedNumberWiring.h"



TEST_GROUP(LedNumber)
{
  LedNumber maxDigits, minDigits;
  int16_t numberWithMaxDigits, numberWithMinDigits;

  void setup()
  {
    mock().strictOrder();
    maxDigits = LedNumber_Create((LedNumber_Place)(LED_UPPER_BOUND-1));
    minDigits = LedNumber_Create((LedNumber_Place)LED_UNITS);

    numberWithMaxDigits = 0;
    for (int i = LED_NONE+1; i < LED_UPPER_BOUND; i++)
    {
      numberWithMaxDigits += i * pow(10, i);
    }

    numberWithMinDigits = 0;
  }

  void teardown()
  {
    LedNumber_Destroy(&maxDigits);
    LedNumber_Destroy(&minDigits);
    mock().checkExpectations();
    mock().clear();
  }
};



//*******************//
//*** Unit Tests  ***//
//*******************//
TEST(LedNumber, Create)
{
  CHECK_TRUE(maxDigits);
}

TEST(LedNumber, Destroy)
{
  LedNumber_Destroy(&maxDigits);
  POINTERS_EQUAL(NULL, maxDigits);
}

TEST(LedNumber, CantCreateNumberLargerThanAllowed)
{
  LedNumber numberTooLarge = LedNumber_Create(LED_UPPER_BOUND);
  POINTERS_EQUAL(NULL, numberTooLarge);
}

TEST(LedNumber, CantCreatNumberWithZeroDigits)
{
  LedNumber numberTooSmall = LedNumber_Create(LED_NONE);
  POINTERS_EQUAL(NULL, numberTooSmall);
}

TEST(LedNumber, DestroyCanHandleNullNumber)
{
  LedNumber_Destroy(NULL);
}

TEST(LedNumber, AllFunctionsCanHandleNull)
{
  LedNumber_SetNumber(NULL, numberWithMaxDigits);
  LedNumber_ShowNumber(NULL);
}

TEST(LedNumber, HardwareSetup)
{
  mock().expectOneCall("LedDigit_HwSetup");
  mock().expectOneCall("LedNumberWiring_HwSetup");
  LedNumber_HwSetup();
}


//*** Test private functions ***//
TEST(LedNumber, ShowNothingAfterCreate)
{
  LedNumber_ShowNumber(maxDigits);
}

TEST(LedNumber, GetUnitsDigitFromNumber)
{
  LONGS_EQUAL(LED_UNITS, LedDigitPrivate_GetDigitFromNumber(numberWithMaxDigits, LED_UNITS));
}

TEST(LedNumber, GetTensDigitFromNumber)
{
  LONGS_EQUAL(LED_TENS, LedDigitPrivate_GetDigitFromNumber(numberWithMaxDigits, LED_TENS));
}

TEST(LedNumber, GetHundredsDigitFromNumber)
{
  LONGS_EQUAL(LED_HUNDREDS, LedDigitPrivate_GetDigitFromNumber(numberWithMaxDigits, LED_HUNDREDS));
}

TEST(LedNumber, GetThousandsDigitFromNumber)
{
  LONGS_EQUAL(LED_THOUSANDS, LedDigitPrivate_GetDigitFromNumber(numberWithMaxDigits, LED_THOUSANDS));
}

TEST(LedNumber, GetAtUpperBoundWhenNoDigit)
{
  LONGS_EQUAL(0, LedDigitPrivate_GetDigitFromNumber(numberWithMaxDigits, LED_UPPER_BOUND));
}

TEST(LedNumber, GetAtUpperBoundWhenDigit)
{
  LONGS_EQUAL(LED_UPPER_BOUND-1, LedDigitPrivate_GetDigitFromNumber(numberWithMaxDigits*10, LED_UPPER_BOUND));
}


//*** Test public functions ***//
TEST(LedNumber, SetMaxDigits)
{
  //Setting the number does nothing visible to the program,
  //so we have nothing to test except compilation
  LedNumber_SetNumber(maxDigits, numberWithMaxDigits);
}

TEST(LedNumber, ShowMaxDigits)
{
  LedNumber_SetNumber(maxDigits, numberWithMaxDigits);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_UNITS);
  expectSetDigit(ZERO);
  expectShowDigit();
  LedNumber_ShowNumber(maxDigits);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_TENS);
  expectSetDigit(ONE);
  expectShowDigit();
  LedNumber_ShowNumber(maxDigits);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_HUNDREDS);
  expectSetDigit(TWO);
  expectShowDigit();
  LedNumber_ShowNumber(maxDigits);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_THOUSANDS);
  expectSetDigit(THREE);
  expectShowDigit();
  LedNumber_ShowNumber(maxDigits);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_UNITS);
  expectSetDigit(ZERO);
  expectShowDigit();
  LedNumber_ShowNumber(maxDigits);
}

TEST(LedNumber, SetBeyondUpperBound)
{
  LedNumber_SetNumber(maxDigits, numberWithMaxDigits*10);
  LedNumber_ShowNumber(maxDigits);
}

TEST(LedNumber, SetMinDigits)
{
  LedNumber_SetNumber(minDigits, numberWithMinDigits);
}

TEST(LedNumber, ShowMinDigits)
{
  LedNumber_SetNumber(minDigits, numberWithMinDigits);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_UNITS);
  expectSetDigit(ZERO);
  expectShowDigit();
  LedNumber_ShowNumber(minDigits);

  expectTurnOffDigit();
  expectSetSelectPin(WIRINGLED_UNITS);
  expectSetDigit(ZERO);
  expectShowDigit();
  LedNumber_ShowNumber(minDigits);
}

TEST(LedNumber, SetBeyondLargestDigit)
{
  LedNumber_SetNumber(minDigits, numberWithMinDigits+10);
  LedNumber_ShowNumber(minDigits);
}
