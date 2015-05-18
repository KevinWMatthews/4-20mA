extern "C"
{
  #include "AtoD.h" //Code under test
  #include "Adc.h"  //HW communication
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_AtoD.h"

TEST_GROUP(AtoDSetup)
{
  void setup()
  {
  }

  void teardown()
  {
    mock().clear();
  }
};

TEST_GROUP(AtoD)
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


//*** Function mocks ***//
BOOL Adc_IsAdcBusy(void)
{
  mock().actualCall("Adc_IsAdcBusy");
  return (BOOL)(mock().intReturnValue());
}

void Adc_StartConversion(void)
{
  mock().actualCall("Adc_StartConversion");
  return;
}

BOOL Adc_IsInterruptFlagSet(void)
{
  mock().actualCall("Adc_IsInterruptFlagSet");
  return (BOOL)(mock().intReturnValue());
}

uint8_t Adc_ReadDataRegister_High(void)
{
  mock().actualCall("Adc_ReadDataRegister_High");
  return mock().intReturnValue();
}

uint8_t Adc_ReadDataRegister_Low(void)
{
  mock().actualCall("Adc_ReadDataRegister_Low");
  return mock().intReturnValue();
}

void Adc_ClearInterruptFlag(void)
{
  mock().actualCall("Adc_ClearInterruptFlag");
  return;
}

//Setup functions mocks
void Adc_SelectReferenceVoltage(Adc_VoltageSource voltageSource)
{
  mock().actualCall("Adc_SelectReferenceVoltage")
        .withParameter("voltageSource", voltageSource);
}

void Adc_SelectResultAdjust(Adc_ResultAdjust resultAdjust)
{
  mock().actualCall("Adc_SelectResultAdjust")
        .withParameter("resultAdjust", resultAdjust);
}

void Adc_SelectInputAndGain(Adc_AnalogInputAndGain inputAndGain)
{
  mock().actualCall("Adc_SelectInputAndGain")
        .withParameter("inputAndGain", inputAndGain);
}

void Adc_SetPrescaleFactor(Adc_PrescaleFactor prescaleFactor)
{
  mock().actualCall("Adc_SetPrescaleFactor")
        .withParameter("prescaleFactor", prescaleFactor);
}

void Adc_Enable(void)
{
  mock().actualCall("Adc_Enable");
}

void Adc_FirstConversion(void)
{
  mock().actualCall("Adc_FirstConversion");
}


//*** The tests! ***//
TEST(AtoD, StartConversion_AdcIsBusy)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(TRUE);
  LONGS_EQUAL(ATOD_BUSY, AtoD_StartConversion());
  mock().checkExpectations();
}

TEST(AtoD, StartConversion_AdcIsFree)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_StartConversion");
  LONGS_EQUAL(ATOD_CONVERSION_STARTED, AtoD_StartConversion());
  mock().checkExpectations();
}

TEST(AtoD, Read_AdcIsBusy)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(TRUE);
  LONGS_EQUAL(ATOD_BUSY, AtoD_Read(&adcReading));
  mock().checkExpectations();
}

TEST(AtoD, Read_InterruptFlagNotSet)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_IsInterruptFlagSet")
        .andReturnValue(FALSE);
  LONGS_EQUAL(ATOD_INTERRUPT_FLAG_NOT_SET, AtoD_Read(&adcReading));
  mock().checkExpectations();
}

TEST(AtoD, Read_SuccessReadZero)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_IsInterruptFlagSet")
        .andReturnValue(TRUE);
  mock().expectOneCall("Adc_ReadDataRegister_Low")
        .andReturnValue(0);
  mock().expectOneCall("Adc_ReadDataRegister_High")
        .andReturnValue(0);
  mock().expectOneCall("Adc_ClearInterruptFlag");
  LONGS_EQUAL(ATOD_READ_SUCCESS, AtoD_Read(&adcReading));
  LONGS_EQUAL(0, adcReading);
  mock().checkExpectations();
}

TEST(AtoD, Read_SuccessReadMax)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_IsInterruptFlagSet")
        .andReturnValue(TRUE);
  mock().expectOneCall("Adc_ReadDataRegister_Low")
        .andReturnValue(0xFF);
  mock().expectOneCall("Adc_ReadDataRegister_High")
        .andReturnValue(0x03);
  mock().expectOneCall("Adc_ClearInterruptFlag");
  LONGS_EQUAL(ATOD_READ_SUCCESS, AtoD_Read(&adcReading));
  LONGS_EQUAL(1023, adcReading);
  mock().checkExpectations();
}

TEST(AtoD, Read_SuccesLowRegisterFullHighRegisterEmpty)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_IsInterruptFlagSet")
        .andReturnValue(TRUE);
  mock().expectOneCall("Adc_ReadDataRegister_Low")
        .andReturnValue(0xFF);
  mock().expectOneCall("Adc_ReadDataRegister_High")
        .andReturnValue(0);
  mock().expectOneCall("Adc_ClearInterruptFlag");
  LONGS_EQUAL(ATOD_READ_SUCCESS, AtoD_Read(&adcReading));
  LONGS_EQUAL(255, adcReading);
  mock().checkExpectations();
}

TEST(AtoD, Read_SuccesLowRegisterEmptyHighRegisterFull)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_IsInterruptFlagSet")
        .andReturnValue(TRUE);
  mock().expectOneCall("Adc_ReadDataRegister_Low")
        .andReturnValue(0);
  mock().expectOneCall("Adc_ReadDataRegister_High")
        .andReturnValue(0x03);
  mock().expectOneCall("Adc_ClearInterruptFlag");
  LONGS_EQUAL(ATOD_READ_SUCCESS, AtoD_Read(&adcReading));
  LONGS_EQUAL(768, adcReading);
  mock().checkExpectations();
}

TEST(AtoD, Read_FilterBadValuesInHighDataRegister)
{
  mock().expectOneCall("Adc_IsAdcBusy")
        .andReturnValue(FALSE);
  mock().expectOneCall("Adc_IsInterruptFlagSet")
        .andReturnValue(TRUE);
  mock().expectOneCall("Adc_ReadDataRegister_Low")
        .andReturnValue(0);
  mock().expectOneCall("Adc_ReadDataRegister_High")
        .andReturnValue(0xFC);
  mock().expectOneCall("Adc_ClearInterruptFlag");
  LONGS_EQUAL(ATOD_READ_SUCCESS, AtoD_Read(&adcReading));
  LONGS_EQUAL(0, adcReading);
  mock().checkExpectations();
}

//Setup test
TEST(AtoDSetup, test)
{
  mock().expectOneCall("Adc_SelectReferenceVoltage")
        .withParameter("voltageSource", ADC_AVCC);
  mock().expectOneCall("Adc_SelectResultAdjust")
        .withParameter("resultAdjust", ADC_RIGHT_ADJUST);
  mock().expectOneCall("Adc_SelectInputAndGain")
        .withParameter("inputAndGain", ADC_SINGLE_ENDED_ADC0);
  mock().expectOneCall("Adc_SetPrescaleFactor")
        .withParameter("prescaleFactor", ADC_PRESCALE_FACTOR_2);
  mock().expectOneCall("Adc_Enable");
  mock().expectOneCall("Adc_FirstConversion");
  AtoD_Setup();
  mock().checkExpectations();
}
