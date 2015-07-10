extern "C"
{
  #include "Adc.h"        //Code under test
  #include "AdcWiring.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_Adc.h"



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



//*******************//
//*** Unit tests! ***//
//*******************//
TEST(Adc, Setup)
{
  mock().expectOneCall("AdcWiring_HwSetup");
  mock().expectOneCall("AdcWiring_Enable");
  mock().expectOneCall("AdcWiring_FirstConversion");
  Adc_HwSetup();
  mock().checkExpectations();
}

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

TEST(Adc, Read_SuccessReadZero)
{
  mock().expectOneCall("AdcWiring_IsAdcBusy")
        .andReturnValue(FALSE);
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
  mock().expectOneCall("AdcWiring_ReadDataRegister_Low")
        .andReturnValue(0);
  mock().expectOneCall("AdcWiring_ReadDataRegister_High")
        .andReturnValue(0xFC);
  mock().expectOneCall("AdcWiring_ClearInterruptFlag");
  LONGS_EQUAL(ADC_READ_SUCCESS, Adc_Read(&adcReading));
  LONGS_EQUAL(0, adcReading);
  mock().checkExpectations();
}
