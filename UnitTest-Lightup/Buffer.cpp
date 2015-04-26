#include <Lightup.h>
#include <gtest/gtest.h>

TEST(BufferTest, Positive) {
	Buffer b1(1);
	EXPECT_EQ(1, b1.Length());
	EXPECT_TRUE(b1.Adress() != NULL);

	Buffer b2(1024);
	EXPECT_EQ(1024, b2.Length());
	EXPECT_TRUE(b2.Adress() != NULL);
}

TEST(BufferTest, Zero) {
	Buffer b1(0);
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Adress() == NULL);
}

TEST(BufferTest, Negtive) {
	// acutally negtive value is not possible
	// because SIZE_T is an unsigned type
	Buffer b1(-1);
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Adress() == NULL);
}

TEST(BufferTest, TooBig) {
	Buffer b1(MAXSIZE_T);
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Adress() == NULL);
}

TEST(BufferTest, CopyConstruct) {
	Buffer b1(128);
	EXPECT_EQ(128, b1.Length());
	EXPECT_TRUE(b1.Length() != NULL);

	for (SIZE_T i = 0; i < b1.Length(); ++i)
	{
		b1.Adress()[i] = (char)i;
	}

	Buffer b2 = b1;
	EXPECT_TRUE(b2.Length() == b1.Length());
	EXPECT_TRUE(b2.Adress() != NULL);
	EXPECT_TRUE(b2.Adress() != b1.Adress());

	for (SIZE_T i = 0; i < b2.Length(); ++i)
	{
		EXPECT_EQ(b2.Adress()[i], b1.Adress()[i]);
	}

	// when we change b1, b2 is not changed

	for (SIZE_T i = 0; i < b1.Length(); ++i)
	{
		b1.Adress()[i] += 1;
	}

	for (SIZE_T i = 0; i < b2.Length(); ++i)
	{
		EXPECT_EQ((char)(b2.Adress()[i] + 1), b1.Adress()[i]);
	}
}

TEST(BufferTest, AssignOperator) {
	Buffer b1(128);
	Buffer b2(256);
	b2 = b1;
	EXPECT_EQ(b1.Length(), b2.Length());
	EXPECT_NE(b1.Adress(), b2.Adress());
	for (SIZE_T i = 0; i < b2.Length(); ++i)
	{
		EXPECT_EQ(b1.Adress()[i], b2.Adress()[i]);
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
	EXPECT_TRUE(b1.Adress() == NULL);

	b1 = (wchar_t*)NULL;
	EXPECT_EQ(b1.Length(), 0);
	EXPECT_TRUE(b1.Adress() == NULL);
}

TEST(BufferTest, AssignWCharStringEmpty) {
	Buffer b1;
	EXPECT_EQ(b1.Length(), 0);
	EXPECT_TRUE(b1.Adress() == NULL);

	b1 = L"";
	EXPECT_EQ(b1.Length(), 2);
	EXPECT_TRUE(b1.Adress() != NULL);
	EXPECT_EQ(b1.Adress()[0], 0);
	EXPECT_EQ(b1.Adress()[1], 0);
}

TEST(BufferTest, AssignWCharString) {
	Buffer b1;
	EXPECT_EQ(b1.Length(), 0);
	EXPECT_TRUE(b1.Adress() == NULL);

	b1 = L"a";
	EXPECT_EQ(b1.Length(), 4);
	EXPECT_TRUE(b1.Adress() != NULL);
	EXPECT_EQ(b1.Adress()[2], 0);
	EXPECT_EQ(b1.Adress()[3], 0);
}