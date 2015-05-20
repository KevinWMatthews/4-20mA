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
