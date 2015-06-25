extern "C"
{
  #include "Adc.h" //Code under test
  #include "AdcWiring.h"  //HW communication
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_Adc.h"

TEST_GROUP(AdcSetup)
{
  void setup()
  {
  }

  void teardown()
  {
    mock().clear();
  }
};

TEST_GROUP(Adc)
{
  int16_t adcReading;

  void setup()
  {
    adcReading = 0;
  }

  void teardown()
  {
    mock().clear();
  }
};

//**************************//
//*** ADC function mocks ***//
//**************************//
BOOL AdcWiring_IsAdcBusy(void)
{
  mock().actualCall("AdcWiring_IsAdcBusy");
  return (BOOL)(mock().intReturnValue());
}

void AdcWiring_StartConversion(void)
{
  mock().actualCall("AdcWiring_StartConversion");
  return;
}

BOOL AdcWiring_IsInterruptFlagSet(void)
{
  mock().actualCall("AdcWiring_IsInterruptFlagSet");
  return (BOOL)(mock().intReturnValue());
}

uint8_t AdcWiring_ReadDataRegister_High(void)
{
  mock().actualCall("AdcWiring_ReadDataRegister_High");
  return mock().intReturnValue();
}

uint8_t AdcWiring_ReadDataRegister_Low(void)
{
  mock().actualCall("AdcWiring_ReadDataRegister_Low");
  return mock().intReturnValue();
}

void AdcWiring_ClearInterruptFlag(void)
{
  mock().actualCall("AdcWiring_ClearInterruptFlag");
  return;
}

//Mock ADC setup functions
void AdcWiring_Init(void)
{
  mock().actualCall("AdcWiring_Init");
}

void AdcWiring_Enable(void)
{
  mock().actualCall("AdcWiring_Enable");
}

void AdcWiring_FirstConversion(void)
{
  mock().actualCall("AdcWiring_FirstConversion");
}


//*** The tests! ***//
TEST(Adc, StartConversion_AdcIsBusy)
{
  mock().expectOneCall("AdcWiring_IsAdcBusy")
        .andReturnValue(TRUE);
  LONGS_EQUAL(ADC_CONVERSION_BUSY, Adc_StartConversion());
  mock().checkExpectations();
}

TEST(Adc, StartConversion_AdcsFree)
{
  mock().expectOneCall("AdcWiring_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("AdcWiring_StartConversion");
  LONGS_EQUAL(ADC_CONVERSION_STARTED, Adc_StartConversion());
  mock().checkExpectations();
}

TEST(Adc, Read_AdcIsBusy)
{
  mock().expectOneCall("AdcWiring_IsAdcBusy")
        .andReturnValue(TRUE);
  LONGS_EQUAL(ADC_READ_BUSY, Adc_Read(&adcReading));
  mock().checkExpectations();
}

// TEST(Adc, Read_InterruptFlagNotSet)
// {
//   mock().expectOneCall("AdcWiring_IsAdcBusy")
//         .andReturnValue(FALSE);
//   mock().expectOneCall("AdcWiring_IsInterruptFlagSet")
//         .andReturnValue(FALSE);
//   LONGS_EQUAL(ADC_INTERRUPT_FLAG_NOT_SET, Adc_Read(&adcReading));
//   mock().checkExpectations();
// }

TEST(Adc, Read_SuccessReadZero)
{
  mock().expectOneCall("AdcWiring_IsAdcBusy")
        .andReturnValue(FALSE);
  // mock().expectOneCall("AdcWiring_IsInterruptFlagSet")
  //       .andReturnValue(TRUE);
  mock().expectOneCall("AdcWiring_ReadDataRegister_Low")
        .andReturnValue(0);
  mock().expectOneCall("AdcWiring_ReadDataRegister_High")
        .andReturnValue(0);
  mock().expectOneCall("AdcWiring_ClearInterruptFlag");
  LONGS_EQUAL(ADC_READ_SUCCESS, Adc_Read(&adcReading));
  LONGS_EQUAL(0, adcReading);
  mock().checkExpectations();
}

TEST(Adc, Read_SuccessReadMax)
{
  mock().expectOneCall("AdcWiring_IsAdcBusy")
        .andReturnValue(FALSE);
  // mock().expectOneCall("AdcWiring_IsInterruptFlagSet")
  //       .andReturnValue(TRUE);
  mock().expectOneCall("AdcWiring_ReadDataRegister_Low")
        .andReturnValue(0xFF);
  mock().expectOneCall("AdcWiring_ReadDataRegister_High")
        .andReturnValue(0x03);
  mock().expectOneCall("AdcWiring_ClearInterruptFlag");
  LONGS_EQUAL(ADC_READ_SUCCESS, Adc_Read(&adcReading));
  LONGS_EQUAL(1023, adcReading);
  mock().checkExpectations();
}

TEST(Adc, Read_SuccesLowRegisterFullHighRegisterEmpty)
{
  mock().expectOneCall("AdcWiring_IsAdcBusy")
        .andReturnValue(FALSE);
  // mock().expectOneCall("AdcWiring_IsInterruptFlagSet")
  //       .andReturnValue(TRUE);
  mock().expectOneCall("AdcWiring_ReadDataRegister_Low")
        .andReturnValue(0xFF);
  mock().expectOneCall("AdcWiring_ReadDataRegister_High")
        .andReturnValue(0);
  mock().expectOneCall("AdcWiring_ClearInterruptFlag");
  LONGS_EQUAL(ADC_READ_SUCCESS, Adc_Read(&adcReading));
  LONGS_EQUAL(255, adcReading);
  mock().checkExpectations();
}

TEST(Adc, Read_SuccesLowRegisterEmptyHighRegisterFull)
{
  mock().expectOneCall("AdcWiring_IsAdcBusy")
        .andReturnValue(FALSE);
  // mock().expectOneCall("AdcWiring_IsInterruptFlagSet")
  //       .andReturnValue(TRUE);
  mock().expectOneCall("AdcWiring_ReadDataRegister_Low")
        .andReturnValue(0);
  mock().expectOneCall("AdcWiring_ReadDataRegister_High")
        .andReturnValue(0x03);
  mock().expectOneCall("AdcWiring_ClearInterruptFlag");
  LONGS_EQUAL(ADC_READ_SUCCESS, Adc_Read(&adcReading));
  LONGS_EQUAL(768, adcReading);
  mock().checkExpectations();
}

TEST(Adc, Read_FilterBadValuesInHighDataRegister)
{
  mock().expectOneCall("AdcWiring_IsAdcBusy")
        .andReturnValue(FALSE);
  // mock().expectOneCall("AdcWiring_IsInterruptFlagSet")
  //       .andReturnValue(TRUE);
  mock().expectOneCall("AdcWiring_ReadDataRegister_Low")
        .andReturnValue(0);
  mock().expectOneCall("AdcWiring_ReadDataRegister_High")
        .andReturnValue(0xFC);
  mock().expectOneCall("AdcWiring_ClearInterruptFlag");
  LONGS_EQUAL(ADC_READ_SUCCESS, Adc_Read(&adcReading));
  LONGS_EQUAL(0, adcReading);
  mock().checkExpectations();
}

//Setup test
TEST(AdcSetup, test)
{
  mock().expectOneCall("AdcWiring_Init");
  mock().expectOneCall("AdcWiring_Enable");
  mock().expectOneCall("AdcWiring_FirstConversion");
  Adc_Setup();
  mock().checkExpectations();
}
