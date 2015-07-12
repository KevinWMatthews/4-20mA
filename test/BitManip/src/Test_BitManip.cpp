extern "C"
{
  #include "BitManip.h"
  #include "DataTypes.h"
}

//CppUTest includes should be after your system includes
#include "CppUTest/TestHarness.h"
#include "Test_BitManip.h"

TEST_GROUP(BitManip)
{
  uint8_t eightBit;

  void setup()
  {
    eightBit = 0;
  }

  void teardown()
  {
  }
};

TEST(BitManip, SetLeastSignificantBitNumber)
{
  SET_BIT_NUMBER(eightBit, 0);

  BYTES_EQUAL(0x01, eightBit);
}

TEST(BitManip, SetMostSignificantBitNumber)
{
  SET_BIT_NUMBER(eightBit, 7);

  BYTES_EQUAL(0x80, eightBit);
}

TEST(BitManip, ClearLeastSignificantBitNumber)
{
  eightBit = 0xff;
  CLEAR_BIT_NUMBER(eightBit, 0);

  BYTES_EQUAL(0xfe, eightBit);
}

TEST(BitManip, ClearMostSignificantBitNumber)
{
  eightBit = 0xff;
  CLEAR_BIT_NUMBER(eightBit, 7);

  BYTES_EQUAL(0x7f, eightBit);
}

TEST(BitManip, IfBitNumber_False)
{
  eightBit = 0xff;
  eightBit &= ~(1<<4);

  CHECK_FALSE(IF_BIT_NUMBER(eightBit, 4));
}

TEST(BitManip, IfBitNumber_True)
{
  eightBit |= (1<<4);

  CHECK_TRUE(IF_BIT_NUMBER(eightBit, 4));
}

TEST(BitManip, SetLeastSignificantBit)
{
  SET_BIT(eightBit, (1<<0));
  BYTES_EQUAL(0x01, eightBit);
}

TEST(BitManip, SetMostSignificantBit)
{
  SET_BIT(eightBit, (1<<7));
  BYTES_EQUAL(0x80, eightBit);
}

TEST(BitManip, ClearLeastSignificantBit)
{
  eightBit = 0xff;
  CLEAR_BIT(eightBit, (1<<0));
  BYTES_EQUAL(0xfe, eightBit);
}

TEST(BitManip, ClearMostSignificantBit)
{
  eightBit = 0xff;
  CLEAR_BIT(eightBit, (1<<7));
  BYTES_EQUAL(0x7f, eightBit);
}

TEST(BitManip, IfBit_False)
{
  eightBit = 0xff;
  eightBit &= ~(1<<5);
  CHECK_FALSE(IF_BIT(eightBit, (1<<5)));
}

TEST(BitManip, IfBit_True)
{
  eightBit |= (1<<5);
  CHECK_TRUE(IF_BIT(eightBit, (1<<5)));
}

TEST(BitManip, IfBitmask_NoBitsToCheck)
{
  CHECK_FALSE(IF_BITMASK(0x00, 0x00, 0));
}

TEST(BitManip, IfBitmask_CheckSingleBit_False)
{
  CHECK_FALSE(IF_BITMASK(0x01, 0x00, 0x01));
}

TEST(BitManip, IfBitmask_CheckSingleBit_True)
{
  CHECK_TRUE(IF_BITMASK(0xff, 0x01, 0x01));
}

TEST(BitManip, IfBitmask_CheckAllBits_False)
{
  CHECK_FALSE(IF_BITMASK(0xff, 0x7f, 0xff));
}

TEST(BitManip, IfBitmask_CheckAllBits_True)
{
  CHECK_TRUE(IF_BITMASK(0xff, 0xff, 0xff));
}

TEST(BitManip, IfBitmask_CheckAllBits_BitsVary_True)
{
  CHECK_TRUE(IF_BITMASK(0xaa, 0xaa, 0xff));
}

TEST(BitManip, IfBitmask_CheckAllBits_BitsVary_False)
{
  CHECK_FALSE(IF_BITMASK(0xaa, 0xab, 0xff));
}

TEST(BitManip, ClearBitmask)
{
  eightBit = 0xff;
  CLEAR_BITMASK(eightBit, 0xaa);
  BYTES_EQUAL(eightBit, 0x55);  //Hey, this is what you get
}

TEST(BitManip, SetBitmask_BitsToSetLimitsValueActuallySet)
{
  SET_BITMASK(eightBit, 0x3c, 0x18);
  BYTES_EQUAL(0x18, eightBit);
}

TEST(BitManip, SetBitmask_WillClearBits)
{
  eightBit = 0xff;
  SET_BITMASK(eightBit, 0x00, 0x18);
  BYTES_EQUAL(eightBit, 0xe7);
}
