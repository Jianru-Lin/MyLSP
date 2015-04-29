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

TEST(BufferTest, IsAllBytesZero) {
	Buffer b1;
	EXPECT_EQ(true, b1.IsAllBytesZero());

	Buffer b2(1);
	EXPECT_EQ(true, b2.IsAllBytesZero());
	b2.Address()[0] = 1;
	EXPECT_EQ(false, b2.IsAllBytesZero());

	Buffer b3(2);
	EXPECT_EQ(true, b3.IsAllBytesZero());
	b3.Address()[0] = 0;
	b3.Address()[1] = 1;
	EXPECT_EQ(false, b3.IsAllBytesZero());
	b3.Address()[0] = 1;
	b3.Address()[1] = 0;
	EXPECT_EQ(false, b3.IsAllBytesZero());
	b3.Address()[0] = 0;
	b3.Address()[1] = 0;
	EXPECT_EQ(true, b3.IsAllBytesZero());

	Buffer b4(3);
	EXPECT_EQ(true, b4.IsAllBytesZero());
	b4.Address()[0] = 1;
	b4.Address()[1] = 0;
	b4.Address()[2] = 0;
	EXPECT_EQ(false, b4.IsAllBytesZero());
	b4.Address()[0] = 0;
	b4.Address()[1] = 1;
	b4.Address()[2] = 0;
	EXPECT_EQ(false, b4.IsAllBytesZero());
	b4.Address()[0] = 0;
	b4.Address()[1] = 0;
	b4.Address()[2] = 1;
	EXPECT_EQ(false, b4.IsAllBytesZero());
	b4.Address()[0] = 0;
	b4.Address()[1] = 0;
	b4.Address()[2] = 0;
	EXPECT_EQ(true, b4.IsAllBytesZero());
}

TEST(BufferTest, Get_) {
	char value = 0;

	Buffer b1;
	EXPECT_FALSE(b1.Get(0, value));
	EXPECT_FALSE(b1.Get(1, value));

	Buffer b2(1);
	EXPECT_TRUE(b2.Get(0, value));
	EXPECT_FALSE(b2.Get(1, value));

	Buffer b3(2);
	EXPECT_TRUE(b3.Get(0, value));
	EXPECT_TRUE(b3.Get(1, value));
	EXPECT_FALSE(b3.Get(2, value));
}

TEST(BufferTest, Set_) {
	char value = 1;

	Buffer b1;
	EXPECT_FALSE(b1.Set(0, value));
	EXPECT_FALSE(b1.Set(1, value));

	Buffer b2(1);
	EXPECT_TRUE(b2.Set(0, value));
	EXPECT_FALSE(b2.Set(1, value));

	Buffer b3(2);
	EXPECT_TRUE(b3.Set(0, value));
	EXPECT_TRUE(b3.Set(1, value));
	EXPECT_FALSE(b3.Set(2, value));
}

TEST(BufferTest, SetGet) {
	char value = 0;

	Buffer b1(1);
	EXPECT_TRUE(b1.Set(0, 3));
	EXPECT_TRUE(b1.Get(0, value));
	EXPECT_EQ(3, value);
}

TEST(BufferTest, GetBufferEmpty) {
	Buffer b1, b2;
	EXPECT_FALSE(b1.Get(0, 0, b2));
	EXPECT_FALSE(b1.Get(0, 1, b2));
}

TEST(BufferTest, GetBufferNotEmpty) {
	Buffer b1(3), b2;
	EXPECT_TRUE(b1.Get(0, 1, b2));
}

TEST(BufferTest, EqualsEmpty) {
	Buffer b1, b2;
	EXPECT_TRUE(b1.Equals(b2));
	EXPECT_TRUE(b2.Equals(b1));
}

TEST(BufferTest, EqualsSelf) {
	Buffer b;
	EXPECT_TRUE(b.Equals(b));
}

TEST(BufferTest, EqualsSameValue) {
	Buffer b1(128), b2(128);
	EXPECT_TRUE(b1.Equals(b2));
	EXPECT_TRUE(b2.Equals(b1));
}

TEST(BufferTest, NotEqualsEmptyAndNotEmpty) {
	Buffer b1, b2(128);
	EXPECT_FALSE(b1.Equals(b2));
	EXPECT_FALSE(b2.Equals(b1));
}

TEST(BufferTest, NotEqualsDiffLen) {
	Buffer b1(64), b2(128);
	EXPECT_FALSE(b1.Equals(b2));
	EXPECT_FALSE(b2.Equals(b1));
}

TEST(BufferTest, NotEqualsDiffByte) {
	Buffer b1(16), b2(16);
	EXPECT_TRUE(b1.Equals(b2));
	EXPECT_TRUE(b2.Equals(b1));

	b1.Address()[0] = 1;
	EXPECT_FALSE(b1.Equals(b2));
	EXPECT_FALSE(b2.Equals(b1));

	b1.Address()[0] = 0;
	b1.Address()[15] = 1;
	EXPECT_FALSE(b1.Equals(b2));
	EXPECT_FALSE(b2.Equals(b1));

	b1.Address()[15] = 0;
	b1.Address()[7] = 1;
	EXPECT_FALSE(b1.Equals(b2));
	EXPECT_FALSE(b2.Equals(b1));
}

TEST(BufferTest, Randomize) {
	Buffer b1;
	b1.Randomize();
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Address() == NULL);
	EXPECT_TRUE(b1.IsAllBytesZero());

	Buffer b2(128);
	EXPECT_TRUE(b2.IsAllBytesZero());
	b2.Randomize();
	EXPECT_FALSE(b2.IsAllBytesZero());
}

TEST(BufferTest, SwapEmpty) {
	Buffer b1, b2;
	b1.Swap(b2);

	Buffer b3, b4(16);
	b3.Swap(b4);
	EXPECT_EQ(16, b3.Length());
	EXPECT_TRUE(b3.Address() != NULL);
	EXPECT_EQ(0, b4.Length());
	EXPECT_TRUE(b4.Address() == NULL);
}

TEST(BufferTest, SwapNotEmpty) {
	Buffer b1(16), b2(64);
	b1.Swap(b2);
	EXPECT_EQ(64, b1.Length());
	EXPECT_EQ(16, b2.Length());
}

TEST(BufferTest, SwapSelf) {
	Buffer b1;
	b1.Swap(b1);
	EXPECT_EQ(0, b1.Length());
	EXPECT_TRUE(b1.Address() == NULL);

	Buffer b2(128);
	b2.Swap(b2);
	EXPECT_EQ(128, b2.Length());
	EXPECT_TRUE(b2.Address() != NULL);
}

TEST(BufferTest, ResizeZero2Zero) {
	Buffer b;
	EXPECT_TRUE(b.Resize(0));
	EXPECT_EQ(0, b.Length());
	EXPECT_TRUE(b.Address() == NULL);
}

TEST(BufferTest, ResizeZero2Positive) {
	Buffer b;
	EXPECT_TRUE(b.Resize(1));
	EXPECT_EQ(1, b.Length());
	EXPECT_TRUE(b.Address() != NULL);
}

TEST(BufferTest, ResizeZero2Big) {
	Buffer b;
	EXPECT_FALSE(b.Resize(MAXSIZE_T));
	EXPECT_EQ(0, b.Length());
	EXPECT_TRUE(b.Address() == NULL);
}

TEST(BufferTest, ResizePositive2Zero) {
	Buffer b(1);
	EXPECT_TRUE(b.Resize(0));
	EXPECT_EQ(0, b.Length());
	EXPECT_TRUE(b.Address() == NULL);
}

TEST(BufferTest, ResizePositive2Positive) {
	Buffer b(13);
	EXPECT_TRUE(b.Resize(33));
	EXPECT_EQ(33, b.Length());
	EXPECT_TRUE(b.Address() != NULL);
}

TEST(BufferTest, ResizeBigger) {
	Buffer b(13);
	for (SIZE_T i = 0; i < b.Length(); ++i)
	{
		b.Address()[i] = (char)i;
	}
	EXPECT_TRUE(b.Resize(23));
	for (SIZE_T i = 0; i < 13; ++i)
	{
		EXPECT_TRUE(b.Address()[i] == i);
	}
	for (SIZE_T i = 13; i < b.Length(); ++i)
	{
		EXPECT_TRUE(b.Address()[i] == 0);
	}
}

TEST(BufferTest, ResizeSmaller) {
	Buffer b(13);
	for (SIZE_T i = 0; i < b.Length(); ++i)
	{
		b.Address()[i] = (char)i;
	}
	EXPECT_TRUE(b.Resize(7));
	for (SIZE_T i = 0; i < b.Length(); ++i)
	{
		EXPECT_TRUE(b.Address()[i] == i);
	}
}
TEST(BufferTest, SaveToFile_LoadFromFile) {
	Buffer b1(100);
	Buffer b2;

	Buffer fileName;
	fileName = "c:\\test.txt";
	EXPECT_TRUE(b1.SaveToFile(fileName));
	EXPECT_TRUE(b2.LoadFromFile(fileName));
	EXPECT_TRUE(b1.Equals(b2));
	b1.Randomize();
	EXPECT_TRUE(b1.SaveToFile(fileName));
	EXPECT_TRUE(b2.LoadFromFile(fileName));
	EXPECT_TRUE(b1.Equals(b2));

	Buffer errorFileName(5);
	errorFileName.Randomize();
	EXPECT_FALSE(b1.SaveToFile(errorFileName));
	EXPECT_FALSE(b2.LoadFromFile(errorFileName));
}