#include "latch.h"
#include "gtest/gtest.h"

class LatchTest : public ::testing::Test {
};


TEST_F(LatchTest, BasicTrueLatch) 
{
  Latch<true> x;
  ASSERT_TRUE(x);

  x = false;
  ASSERT_FALSE(x);

  x = true;
  ASSERT_FALSE(x);

  x.Reset();
  ASSERT_TRUE(x);
}

TEST_F(LatchTest, BasicFalseLatch) 
{
  Latch<false> x;
  ASSERT_FALSE(x);

  x = true;
  ASSERT_TRUE(x);

  x = false;
  ASSERT_TRUE(x);

  x.Reset();
  ASSERT_FALSE(x);
}

TEST_F(LatchTest, CopyTest)
{
  Latch<true> tl;
  Latch<false> fl;

  ASSERT_TRUE(tl);
  ASSERT_FALSE(fl);

  tl = fl;
  ASSERT_FALSE(tl);

  fl = !tl;
  ASSERT_TRUE(fl);
}