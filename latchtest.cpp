#include "gtest/gtest.h"
#include "latch.h"

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

	x = Latch<true>();
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

	x = Latch<false>();
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

TEST_F(LatchTest, CallbackLatch)
{
	Latch<false> x;
	ASSERT_FALSE(x);

	int f = 0;
	int t = 0;
	x.onAssigned(false, [&f]() { f++; });
	x.onAssigned(true, [&t]() { t++; });

	x = true;
	ASSERT_EQ(t, 1);
	ASSERT_EQ(f, 0);
	ASSERT_TRUE(x);

	x = true;
	ASSERT_EQ(t, 2);
	ASSERT_EQ(f, 0);
	ASSERT_TRUE(x);

	x = false;
	ASSERT_EQ(t, 2);
	ASSERT_EQ(f, 1);
	ASSERT_TRUE(x);

	x = false;
	ASSERT_EQ(t, 2);
	ASSERT_EQ(f, 2);
	ASSERT_TRUE(x);

	x.onAssigned(false, nullptr);
	x.onAssigned(true, nullptr);

	x = false;
	ASSERT_EQ(t, 2);
	ASSERT_EQ(f, 2);
	ASSERT_TRUE(x);

	x = Latch<false>();
	ASSERT_FALSE(x);
}

TEST_F(LatchTest, CallbackRetval)
{
	Latch<false> x;
	Latch<false>::CallbackT old;
	old = x.onAssigned(true, [] {});
	ASSERT_FALSE(old);
	ASSERT_TRUE(x.onAssigned(true, old));
}

TEST_F(LatchTest, CallbackTryCatch)
{
	Latch<true> x;
	ASSERT_TRUE(x);
	x.onAssigned(false, [] { throw std::runtime_error("alldone"); });

	try
	{
		ASSERT_TRUE(x = true);
		ASSERT_TRUE(x = true);
		ASSERT_FALSE(x = false);
		ASSERT_TRUE(x = true); //unreached
	}
	catch (const std::runtime_error&)
	{
		ASSERT_FALSE(x);
	}

	ASSERT_FALSE(x);
}