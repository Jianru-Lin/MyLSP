#include <Lightup.h>
#include <gtest/gtest.h>

TEST(BufferTest, Positive) {
	Buffer b1(1);
	EXPECT_EQ(1, b1.Length());
	EXPECT_TRUE(b1.Address() != NULL);

	Buffer b2(1024);
	EXPECT_EQ(1024, b2.Length());
	EXPECT_TRUE(b2.Address() != NULL);
}

TEST(BufferTest, Zero) {
	Buffer b1(0);
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Address() == NULL);
}

TEST(BufferTest, Negtive) {
	// acutally negtive value is not possible
	// because SIZE_T is an unsigned type
	Buffer b1(-1);
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Address() == NULL);
}

TEST(BufferTest, TooBig) {
	Buffer b1(MAXSIZE_T);
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Address() == NULL);
}

TEST(BufferTest, ReAllocZero) {
	Buffer b1;
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Address() == NULL);

	EXPECT_EQ(true, b1.ReAlloc(0));
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Address() == NULL);

	Buffer b2(128);
	EXPECT_EQ(128, b2.Length());
	EXPECT_TRUE(b2.Address() != NULL);

	EXPECT_EQ(true, b2.ReAlloc(0));
	EXPECT_EQ(0, b2.Length());
	EXPECT_TRUE(b2.Address() == NULL);
}

TEST(BufferTest, ReAllocPositive) {
	Buffer b1;
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Address() == NULL);

	EXPECT_EQ(true, b1.ReAlloc(13));
	EXPECT_EQ(13, b1.Length());
	EXPECT_TRUE(b1.Address() != NULL);

	Buffer b2(128);
	EXPECT_EQ(128, b2.Length());
	EXPECT_TRUE(b2.Address() != NULL);

	EXPECT_EQ(true, b2.ReAlloc(13));
	EXPECT_EQ(13, b2.Length());
	EXPECT_TRUE(b2.Address() != NULL);
}

TEST(BufferTest, ReAllocTooBig) {
	Buffer b1;
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Address() == NULL);

	EXPECT_EQ(false, b1.ReAlloc(MAXSIZE_T));
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Address() == NULL);

	Buffer b2(128);
	EXPECT_EQ(128, b2.Length());
	EXPECT_TRUE(b2.Address() != NULL);

	EXPECT_EQ(false, b2.ReAlloc(MAXSIZE_T));
	EXPECT_EQ(0, b2.Length());
	EXPECT_TRUE(b2.Address() == NULL);
}

TEST(BufferTest, CopyConstruct) {
	Buffer b1(128);
	EXPECT_EQ(128, b1.Length());
	EXPECT_TRUE(b1.Length() != NULL);

	for (SIZE_T i = 0; i < b1.Length(); ++i)
	{
		b1.Address()[i] = (char)i;
	}

	Buffer b2 = b1;
	EXPECT_TRUE(b2.Length() == b1.Length());
	EXPECT_TRUE(b2.Address() != NULL);
	EXPECT_TRUE(b2.Address() != b1.Address());

	for (SIZE_T i = 0; i < b2.Length(); ++i)
	{
		EXPECT_EQ(b2.Address()[i], b1.Address()[i]);
	}

	// when we change b1, b2 is not changed

	for (SIZE_T i = 0; i < b1.Length(); ++i)
	{
		b1.Address()[i] += 1;
	}

	for (SIZE_T i = 0; i < b2.Length(); ++i)
	{
		EXPECT_EQ((char)(b2.Address()[i] + 1), b1.Address()[i]);
	}
}

TEST(BufferTest, AssignOperator) {
	Buffer b1(128);
	Buffer b2(256);
	b2 = b1;
	EXPECT_EQ(b1.Length(), b2.Length());
	EXPECT_NE(b1.Address(), b2.Address());
	for (SIZE_T i = 0; i < b2.Length(); ++i)
	{
		EXPECT_EQ(b1.Address()[i], b2.Address()[i]);
	}
}

TEST(BufferTest, AssignOperatorSelf) {
	Buffer b1(128);
	b1 = b1;
	b1 = b1 = b1;
}

TEST(BufferTest, AssignWCharStringNULL) {
	Buffer b1;
	EXPECT_EQ(b1.Length(), 0);
	EXPECT_TRUE(b1.Address() == NULL);

	b1 = (wchar_t*)NULL;
	EXPECT_EQ(b1.Length(), 0);
	EXPECT_TRUE(b1.Address() == NULL);
}

TEST(BufferTest, AssignWCharStringEmpty) {
	Buffer b1;
	EXPECT_EQ(b1.Length(), 0);
	EXPECT_TRUE(b1.Address() == NULL);

	b1 = L"";
	EXPECT_EQ(b1.Length(), 2);
	EXPECT_TRUE(b1.Address() != NULL);
	EXPECT_EQ(b1.Address()[0], 0);
	EXPECT_EQ(b1.Address()[1], 0);
}

TEST(BufferTest, AssignWCharString) {
	Buffer b1;
	EXPECT_EQ(b1.Length(), 0);
	EXPECT_TRUE(b1.Address() == NULL);

	b1 = L"a";
	EXPECT_EQ(b1.Length(), 4);
	EXPECT_TRUE(b1.Address() != NULL);
	EXPECT_EQ(b1.Address()[2], 0);
	EXPECT_EQ(b1.Address()[3], 0);
}