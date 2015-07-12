extern "C"
{
  #include "MainLoop.h"
  #include "TimeService.h"
  #include "Adc.h"
  #include "LineFit.h"
  #include "LedNumber.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Test_MainLoop.h"

#define ADC_INITIAL_VALUE 12
#define FOURTOTWENTY_INITIAL_VALUE 12

static int16_t ledNumberDeadDrop;
static void * dummyPointer;

TEST_GROUP(MainLoop)
{
  PeriodicAlarm AdcConversion, getReading, displayUpdate;
  getReadingParameterStruct getReadingParameters;
  LineFit fourToTwentyLine;
  LedNumber ledDisplay;
  void * nullPointer;

  void setup()
  {
    nullPointer = NULL;
    dummyPointer = &dummyPointer;
    TimeService_Create();

    AdcConversion = TimeService_AddPeriodicAlarm(MainLoop_AdcConversion, 1000);
    getReading = TimeService_AddPeriodicAlarm(MainLoop_GetReading, 10); //What amount of time should we use?
    displayUpdate = TimeService_AddPeriodicAlarm(MainLoop_UpdateDisplay, 250);

    fourToTwentyLine = (LineFit)dummyPointer;
    ledDisplay = (LedNumber)dummyPointer;

    getReadingParameters.outputModel = fourToTwentyLine;
    getReadingParameters.ledDisplay = ledDisplay;
    getReadingParameters.getReadingAlarm = getReading;

    ledNumberDeadDrop = 0;
  }

  void teardown()
  {
    mock().checkExpectations();
    mock().clear();
  }
};

//*** Function mocks ***//
int8_t Adc_StartConversion(void)
{
  mock().actualCall("Adc_StartConversion");
  return mock().intReturnValue();
}

int8_t Adc_Read(int16_t * adcReading)
{
  mock().actualCall("Adc_Read")
        .withOutputParameter("adcReading", adcReading);
  return mock().intReturnValue();
}

float LineFit_GetOutput(LineFit self, int16_t x)
{
  mock().actualCall("LineFit_GetOutput");
  return mock().intReturnValue();
}

void LedNumber_SetNumber(LedNumber self, int16_t number)
{
  mock().actualCall("LedNumber_SetNumber")
        .withParameter("self", self)
        .withParameter("number", number);
  ledNumberDeadDrop = number;
}

void LedNumber_ShowNumber(LedNumber self)
{
  mock().actualCall("LedNumber_ShowNumber");
}


TEST(MainLoop, NoCallbacksIfIsntTime)
{
  TimeService_ActivatePeriodicAlarm(AdcConversion);
  TimeService_ActivatePeriodicAlarm(getReading);
  TimeService_ActivatePeriodicAlarm(displayUpdate);
  TimeService_TimerTick();
  TimeService_ServiceSingleCallback(AdcConversion, (void*)&getReading);
  TimeService_ServiceSingleCallback(getReading, nullPointer);
  TimeService_ServiceSingleCallback(displayUpdate, nullPointer);
}

TEST(MainLoop, AdcConversionExecutesIfTime)
{
  TimeService_ActivatePeriodicAlarm(AdcConversion);
  TimeServicePrivate_SetCounter(AdcConversion, 999);
  TimeService_TimerTick();
  mock().expectOneCall("Adc_StartConversion")
        .andReturnValue(ADC_CONVERSION_STARTED);
  TimeService_ServiceSingleCallback(AdcConversion, (void*)&getReading);
  LONGS_EQUAL(PA_COUNTER_RESET_VALUE, TimeServicePrivate_GetCounter(getReading));
}

TEST(MainLoop, ReadAdcExitsImmediatelyIfConversionWasBusy)
{
  TimeService_ActivatePeriodicAlarm(getReading);
  TimeServicePrivate_SetCounter(getReading, 9);
  MainLoop_Private_SetAdcConversionStatus(ADC_CONVERSION_BUSY);
  TimeService_TimerTick();

  TimeService_ServiceSingleCallback(getReading, (void*)&getReadingParameters);
  LONGS_EQUAL(0, ledNumberDeadDrop);
}

TEST(MainLoop, ReadAdcExitsIfReadBusy)
{
  int16_t adcOutput = 14;

  TimeService_ActivatePeriodicAlarm(getReading);
  TimeServicePrivate_SetCounter(getReading, 9);
  MainLoop_Private_SetAdcConversionStatus(ADC_CONVERSION_STARTED);
  TimeService_TimerTick();

  mock().expectOneCall("Adc_Read")
        .withOutputParameterReturning("adcReading", &adcOutput, sizeof(int16_t))
        .andReturnValue(ADC_READ_BUSY);

  TimeService_ServiceSingleCallback(getReading, (void*)&getReadingParameters);
  LONGS_EQUAL(0, ledNumberDeadDrop);
}

TEST(MainLoop, ReadAdcSuccess)
{
  int16_t adcOutput = 1000;
  TimeService_ActivatePeriodicAlarm(getReading);
  TimeServicePrivate_SetCounter(getReading, 9);
  MainLoop_Private_SetAdcConversionStatus(ADC_CONVERSION_STARTED);
  TimeService_TimerTick();

  mock().expectOneCall("Adc_Read")
        .withOutputParameterReturning("adcReading", &adcOutput, sizeof(int16_t))
        .andReturnValue(ADC_READ_SUCCESS);
  mock().expectOneCall("LineFit_GetOutput")
        .andReturnValue(20);
  mock().expectOneCall("LedNumber_SetNumber")
        .withParameter("self", ledDisplay)
        .withParameter("number", 20);

  TimeService_ServiceSingleCallback(getReading, (void*)&getReadingParameters);
  LONGS_EQUAL(20, ledNumberDeadDrop);
  LONGS_EQUAL(PA_INACTIVE, TimeServicePrivate_GetCounter(getReading));
}

TEST(MainLoop, UpdateDisplayExecutesIfItsTime)
{
  TimeService_ActivatePeriodicAlarm(displayUpdate);
  TimeServicePrivate_SetCounter(displayUpdate, 249);
  TimeService_TimerTick();
  mock().expectOneCall("LedNumber_ShowNumber");
  TimeService_ServiceSingleCallback(displayUpdate, (void*)ledDisplay);
}
