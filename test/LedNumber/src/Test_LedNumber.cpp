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

  void expectShowNumber(LedNumberWiring_Place place, LedDigit_Value number)
  {
    expectTurnOffDigit();
    expectSetSelectPin(place);
    expectSetDigit(number);
    expectShowDigit();
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
  expectShowNumber(WIRINGLED_UNITS, NO_DIGIT);
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

  expectShowNumber(WIRINGLED_UNITS, ZERO);
  LedNumber_ShowNumber(maxDigits);

  expectShowNumber(WIRINGLED_TENS, ONE);
  LedNumber_ShowNumber(maxDigits);

  expectShowNumber(WIRINGLED_HUNDREDS, TWO);
  LedNumber_ShowNumber(maxDigits);

  expectShowNumber(WIRINGLED_THOUSANDS, THREE);
  LedNumber_ShowNumber(maxDigits);

  expectShowNumber(WIRINGLED_UNITS, ZERO);
  LedNumber_ShowNumber(maxDigits);
}

TEST(LedNumber, CurrentDigitIncrementsRegardlessOfSetNumber)
{
  LedNumber_SetNumber(maxDigits, numberWithMaxDigits);

  expectShowNumber(WIRINGLED_UNITS, ZERO);
  LedNumber_ShowNumber(maxDigits);

  LedNumber_SetNumber(maxDigits, numberWithMaxDigits);

  expectShowNumber(WIRINGLED_TENS, ONE);
  LedNumber_ShowNumber(maxDigits);
}

TEST(LedNumber, SetBeyondUpperBound)
{
  LedNumber_SetNumber(maxDigits, numberWithMaxDigits*10);
  expectShowNumber(WIRINGLED_UNITS, NO_DIGIT);
  LedNumber_ShowNumber(maxDigits);
}

TEST(LedNumber, SetMinDigits)
{
  LedNumber_SetNumber(minDigits, numberWithMinDigits);
}

TEST(LedNumber, ShowMinDigits)
{
  LedNumber_SetNumber(minDigits, numberWithMinDigits);

  expectShowNumber(WIRINGLED_UNITS, ZERO);
  LedNumber_ShowNumber(minDigits);

  expectShowNumber(WIRINGLED_UNITS, ZERO);
  LedNumber_ShowNumber(minDigits);
}

TEST(LedNumber, SetBeyondLargestDigit)
{
  LedNumber_SetNumber(minDigits, numberWithMinDigits+10);
  expectShowNumber(WIRINGLED_UNITS, NO_DIGIT);
  LedNumber_ShowNumber(minDigits);
}
