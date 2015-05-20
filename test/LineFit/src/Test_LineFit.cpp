extern "C"
{
  #include "LineFit.h"
  #include "DataTypes.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"
#include "Test_LineFit.h"

TEST_GROUP(LineFit)
{
  #define LINE_FIT_PRECISION 0.000001
  LineFit line;

  void setup()
  {
    line = LineFit_Create();
  }

  void teardown()
  {
    LineFit_Destroy(&line);
  }
};

TEST(LineFit, Create)
{
  //TODO learn how to detect a memory leak if free() isn't called
}

TEST(LineFit, DestroyCanHandleNullPointer)
{
  LineFit_Destroy(NULL);
}

TEST(LineFit, DestroyCanHandlePointerToNull)
{
  LineFit pointer = NULL;
  LineFit_Destroy(&pointer);
}

TEST(LineFit, DestroyClearsPointer)
{
  LineFit_Destroy(&line);
  POINTERS_EQUAL(NULL, line);
}

TEST(LineFit, AllFunctionsCanHandleNullPointer)
{
  LineFit_SetPoint1(NULL, 42, 42);
  LineFit_SetPoint2(NULL, 666, 666);
  LineFit_CalculateEquation(NULL);
  LineFit_GetOutput(NULL, 0);
}

TEST(LineFit, CalculateFailsIfPointsNotSet)
{
  LONGS_EQUAL(LINE_FIT_FAIL_VERTICAL_LINE, LineFit_CalculateEquation(line));
}

TEST(LineFit, GetOutputReturnsZeroIfPointsNotSet)
{
  DOUBLES_EQUAL(0.0, LineFit_GetOutput(NULL, 0), LINE_FIT_PRECISION);
  DOUBLES_EQUAL(0.0, LineFit_GetOutput(NULL, -9999), LINE_FIT_PRECISION);
  DOUBLES_EQUAL(0.0, LineFit_GetOutput(NULL, 9999), LINE_FIT_PRECISION);
}

TEST(LineFit, HorizontalLine)
{
  int16_t testOutput = 10;
  LineFit_SetPoint1(line, -2, testOutput);
  LineFit_SetPoint2(line, 2, testOutput);
  LONGS_EQUAL(LINE_FIT_SUCCESS, LineFit_CalculateEquation(line));
  DOUBLES_EQUAL(testOutput, LineFit_GetOutput(line, 0), LINE_FIT_PRECISION);
  DOUBLES_EQUAL(testOutput, LineFit_GetOutput(line, -10), LINE_FIT_PRECISION);
  DOUBLES_EQUAL(testOutput, LineFit_GetOutput(line, 10), LINE_FIT_PRECISION);
}

TEST(LineFit, VerticalLineFails)
{
  int16_t testOutput = 10;
  LineFit_SetPoint1(line, 2, testOutput);
  LineFit_SetPoint2(line, 2, testOutput);
  LONGS_EQUAL(LINE_FIT_FAIL_VERTICAL_LINE, LineFit_CalculateEquation(line));
}

TEST(LineFit, FractionalSlope)
{
  LineFit_SetPoint1(line, 0, 0);
  LineFit_SetPoint2(line, 30, 10);
  LONGS_EQUAL(LINE_FIT_SUCCESS, LineFit_CalculateEquation(line));
  DOUBLES_EQUAL(-10, LineFit_GetOutput(line, -30), LINE_FIT_PRECISION);
}

TEST(LineFit, FractionalIntercept)
{
  LineFit_SetPoint1(line, 29, 9);
  LineFit_SetPoint2(line, 59, 19);
  LONGS_EQUAL(LINE_FIT_SUCCESS, LineFit_CalculateEquation(line));
  DOUBLES_EQUAL(-0.666666, LineFit_GetOutput(line, 0), LINE_FIT_PRECISION);
}
