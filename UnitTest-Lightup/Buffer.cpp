#include <Lightup.h>
#include <gtest/gtest.h>

TEST(BufferTest, DefaultConstructor) {
	Buffer *buf = new Buffer();
// 	EXPECT_TRUE(buf->isRawMode());
// 	EXPECT_EQ(buf->RawAddress(), NULL);
// 	EXPECT_EQ(buf->RawLength(), 0);
// 
// 	BSIZE_T len = 0;
// 	EXPECT_FALSE(buf->StrLength(len));
	delete buf;
}

TEST(BufferTest, SizeConstructor) {
	Buffer *buf = new Buffer((BSIZE_T)0);
	delete buf;
}

TEST(BufferTest, CharConstructor) {
	Buffer *buf = new Buffer("");
	delete buf;
}

/*
TEST(BufferTest, Positive) {
	Buffer b1(1);
	EXPECT_EQ(1, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() != NULL);

	Buffer b2(1024);
	EXPECT_EQ(1024, b2.RawLength());
	EXPECT_TRUE(b2.RawAddress() != NULL);
}

TEST(BufferTest, Zero) {
	Buffer b1((BSIZE_T)0);
	EXPECT_EQ(0, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() == NULL);
}

TEST(BufferTest, Negtive) {
	Buffer b1(-1);
	EXPECT_EQ(0, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() == NULL);
}

TEST(BufferTest, TooBig) {
	Buffer b1(MAXBSIZE_T);
	EXPECT_EQ(0, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() == NULL);
}

TEST(BufferTest, ReAllocZero) {
	Buffer b1;
	EXPECT_EQ(0, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() == NULL);

	EXPECT_EQ(true, b1.RawReAlloc(0));
	EXPECT_EQ(0, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() == NULL);

	Buffer b2(128);
	EXPECT_EQ(128, b2.RawLength());
	EXPECT_TRUE(b2.RawAddress() != NULL);

	EXPECT_EQ(true, b2.RawReAlloc(0));
	EXPECT_EQ(0, b2.RawLength());
	EXPECT_TRUE(b2.RawAddress() == NULL);
}

TEST(BufferTest, ReAllocPositive) {
	Buffer b1;
	EXPECT_EQ(0, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() == NULL);

	EXPECT_EQ(true, b1.RawReAlloc(13));
	EXPECT_EQ(13, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() != NULL);

	Buffer b2(128);
	EXPECT_EQ(128, b2.RawLength());
	EXPECT_TRUE(b2.RawAddress() != NULL);

	EXPECT_EQ(true, b2.RawReAlloc(13));
	EXPECT_EQ(13, b2.RawLength());
	EXPECT_TRUE(b2.RawAddress() != NULL);
}

TEST(BufferTest, ReAllocTooBig) {
	Buffer b1;
	EXPECT_EQ(0, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() == NULL);

	EXPECT_EQ(false, b1.RawReAlloc(MAXBSIZE_T));
	EXPECT_EQ(0, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() == NULL);

	Buffer b2(128);
	EXPECT_EQ(128, b2.RawLength());
	EXPECT_TRUE(b2.RawAddress() != NULL);

	EXPECT_EQ(false, b2.RawReAlloc(MAXBSIZE_T));
	EXPECT_EQ(0, b2.RawLength());
	EXPECT_TRUE(b2.RawAddress() == NULL);
}

TEST(BufferTest, CopyConstruct) {
	Buffer b1(128);
	EXPECT_EQ(128, b1.RawLength());
	EXPECT_TRUE(b1.RawLength() != NULL);

	for (BSIZE_T i = 0; i < b1.RawLength(); ++i)
	{
		b1.RawAddress()[i] = (char)i;
	}

	Buffer b2 = b1;
	EXPECT_TRUE(b2.RawLength() == b1.RawLength());
	EXPECT_TRUE(b2.RawAddress() != NULL);
	EXPECT_TRUE(b2.RawAddress() != b1.RawAddress());

	for (BSIZE_T i = 0; i < b2.RawLength(); ++i)
	{
		EXPECT_EQ(b2.RawAddress()[i], b1.RawAddress()[i]);
	}

	// when we change b1, b2 is not changed

	for (BSIZE_T i = 0; i < b1.RawLength(); ++i)
	{
		b1.RawAddress()[i] += 1;
	}

	for (BSIZE_T i = 0; i < b2.RawLength(); ++i)
	{
		EXPECT_EQ((char)(b2.RawAddress()[i] + 1), b1.RawAddress()[i]);
	}
}

TEST(BufferTest, AssignOperator) {
	Buffer b1(128);
	Buffer b2(256);
	b2 = b1;
	EXPECT_EQ(b1.RawLength(), b2.RawLength());
	EXPECT_NE(b1.RawAddress(), b2.RawAddress());
	for (BSIZE_T i = 0; i < b2.RawLength(); ++i)
	{
		EXPECT_EQ(b1.RawAddress()[i], b2.RawAddress()[i]);
	}
}

TEST(BufferTest, AssignOperatorSelf) {
	Buffer b1(128);
	b1 = b1;
	b1 = b1 = b1;
}

TEST(BufferTest, AssignWCharStringNULL) {
	Buffer b1;
	EXPECT_EQ(b1.RawLength(), 0);
	EXPECT_TRUE(b1.RawAddress() == NULL);

	b1 = (wchar_t*)NULL;
	EXPECT_EQ(b1.RawLength(), 0);
	EXPECT_TRUE(b1.RawAddress() == NULL);
}

TEST(BufferTest, AssignWCharStringEmpty) {
	Buffer b1;
	EXPECT_EQ(b1.RawLength(), 0);
	EXPECT_TRUE(b1.RawAddress() == NULL);

	b1 = L"";
	EXPECT_EQ(b1.RawLength(), 2);
	EXPECT_TRUE(b1.RawAddress() != NULL);
	EXPECT_EQ(b1.RawAddress()[0], 0);
	EXPECT_EQ(b1.RawAddress()[1], 0);
}

TEST(BufferTest, AssignWCharString) {
	Buffer b1;
	EXPECT_EQ(b1.RawLength(), 0);
	EXPECT_TRUE(b1.RawAddress() == NULL);

	b1 = L"a";
	EXPECT_EQ(b1.RawLength(), 4);
	EXPECT_TRUE(b1.RawAddress() != NULL);
	EXPECT_EQ(b1.RawAddress()[2], 0);
	EXPECT_EQ(b1.RawAddress()[3], 0);
}

TEST(BufferTest, IsAllBytesZero) {
	Buffer b1;
	EXPECT_EQ(true, b1.RawIsAllBytesZero());

	Buffer b2(1);
	EXPECT_EQ(true, b2.RawIsAllBytesZero());
	b2.RawAddress()[0] = 1;
	EXPECT_EQ(false, b2.RawIsAllBytesZero());

	Buffer b3(2);
	EXPECT_EQ(true, b3.RawIsAllBytesZero());
	b3.RawAddress()[0] = 0;
	b3.RawAddress()[1] = 1;
	EXPECT_EQ(false, b3.RawIsAllBytesZero());
	b3.RawAddress()[0] = 1;
	b3.RawAddress()[1] = 0;
	EXPECT_EQ(false, b3.RawIsAllBytesZero());
	b3.RawAddress()[0] = 0;
	b3.RawAddress()[1] = 0;
	EXPECT_EQ(true, b3.RawIsAllBytesZero());

	Buffer b4(3);
	EXPECT_EQ(true, b4.RawIsAllBytesZero());
	b4.RawAddress()[0] = 1;
	b4.RawAddress()[1] = 0;
	b4.RawAddress()[2] = 0;
	EXPECT_EQ(false, b4.RawIsAllBytesZero());
	b4.RawAddress()[0] = 0;
	b4.RawAddress()[1] = 1;
	b4.RawAddress()[2] = 0;
	EXPECT_EQ(false, b4.RawIsAllBytesZero());
	b4.RawAddress()[0] = 0;
	b4.RawAddress()[1] = 0;
	b4.RawAddress()[2] = 1;
	EXPECT_EQ(false, b4.RawIsAllBytesZero());
	b4.RawAddress()[0] = 0;
	b4.RawAddress()[1] = 0;
	b4.RawAddress()[2] = 0;
	EXPECT_EQ(true, b4.RawIsAllBytesZero());
}

TEST(BufferTest, Get_) {
	char value = 0;

	Buffer b1;
	EXPECT_FALSE(b1.RawGet(0, value));
	EXPECT_FALSE(b1.RawGet(1, value));

	Buffer b2(1);
	EXPECT_TRUE(b2.RawGet(0, value));
	EXPECT_FALSE(b2.RawGet(1, value));

	Buffer b3(2);
	EXPECT_TRUE(b3.RawGet(0, value));
	EXPECT_TRUE(b3.RawGet(1, value));
	EXPECT_FALSE(b3.RawGet(2, value));
}

TEST(BufferTest, Set_) {
	char value = 1;

	Buffer b1;
	EXPECT_FALSE(b1.RawSet(0, value));
	EXPECT_FALSE(b1.RawSet(1, value));

	Buffer b2(1);
	EXPECT_TRUE(b2.RawSet(0, value));
	EXPECT_FALSE(b2.RawSet(1, value));

	Buffer b3(2);
	EXPECT_TRUE(b3.RawSet(0, value));
	EXPECT_TRUE(b3.RawSet(1, value));
	EXPECT_FALSE(b3.RawSet(2, value));
}

TEST(BufferTest, SetGet) {
	char value = 0;

	Buffer b1(1);
	EXPECT_TRUE(b1.RawSet(0, 3));
	EXPECT_TRUE(b1.RawGet(0, value));
	EXPECT_EQ(3, value);
}

TEST(BufferTest, GetBufferEmpty) {
	Buffer b1, b2;
	EXPECT_FALSE(b1.RawGet(0, 0, b2));
	EXPECT_FALSE(b1.RawGet(0, 1, b2));
}

TEST(BufferTest, GetBufferNotEmpty) {
	char value = 0;
	Buffer b1(3), b2;
	b1.RawSet(1, 3);
	EXPECT_TRUE(b1.RawGet(1, 1, b2));
	EXPECT_TRUE(b2.RawGet(0, value));
	EXPECT_EQ(3, value);
}

TEST(BufferTest, SetBuffer) {
	Buffer b1, b2;
	EXPECT_FALSE(b1.RawSet(0, b2));
	
	Buffer b3, b4(13);
	EXPECT_FALSE(b3.RawSet(0, b4));

	Buffer b5(13), b6(13);
	EXPECT_TRUE(b5.RawSet(0, b6));
	EXPECT_FALSE(b5.RawSet(1, b6));

	Buffer b7(13), b8(14);
	EXPECT_FALSE(b7.RawSet(0, b8));
}

TEST(BufferTest, EqualsEmpty) {
	Buffer b1, b2;
	EXPECT_TRUE(b1.RawEquals(b2));
	EXPECT_TRUE(b2.RawEquals(b1));
}

TEST(BufferTest, EqualsSelf) {
	Buffer b;
	EXPECT_TRUE(b.RawEquals(b));
}

TEST(BufferTest, EqualsSameValue) {
	Buffer b1(128), b2(128);
	EXPECT_TRUE(b1.RawEquals(b2));
	EXPECT_TRUE(b2.RawEquals(b1));
}

TEST(BufferTest, NotEqualsEmptyAndNotEmpty) {
	Buffer b1, b2(128);
	EXPECT_FALSE(b1.RawEquals(b2));
	EXPECT_FALSE(b2.RawEquals(b1));
}

TEST(BufferTest, NotEqualsDiffLen) {
	Buffer b1(64), b2(128);
	EXPECT_FALSE(b1.RawEquals(b2));
	EXPECT_FALSE(b2.RawEquals(b1));
}

TEST(BufferTest, NotEqualsDiffByte) {
	Buffer b1(16), b2(16);
	EXPECT_TRUE(b1.RawEquals(b2));
	EXPECT_TRUE(b2.RawEquals(b1));

	b1.RawAddress()[0] = 1;
	EXPECT_FALSE(b1.RawEquals(b2));
	EXPECT_FALSE(b2.RawEquals(b1));

	b1.RawAddress()[0] = 0;
	b1.RawAddress()[15] = 1;
	EXPECT_FALSE(b1.RawEquals(b2));
	EXPECT_FALSE(b2.RawEquals(b1));

	b1.RawAddress()[15] = 0;
	b1.RawAddress()[7] = 1;
	EXPECT_FALSE(b1.RawEquals(b2));
	EXPECT_FALSE(b2.RawEquals(b1));
}

TEST(BufferTest, Randomize) {
	Buffer b1;
	b1.RawRandomize();
	EXPECT_EQ(0, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() == NULL);
	EXPECT_TRUE(b1.RawIsAllBytesZero());

	Buffer b2(128);
	EXPECT_TRUE(b2.RawIsAllBytesZero());
	b2.RawRandomize();
	EXPECT_FALSE(b2.RawIsAllBytesZero());
}

TEST(BufferTest, SwapEmpty) {
	Buffer b1, b2;
	b1.SwapWith(b2);

	Buffer b3, b4(16);
	b3.SwapWith(b4);
	EXPECT_EQ(16, b3.RawLength());
	EXPECT_TRUE(b3.RawAddress() != NULL);
	EXPECT_EQ(0, b4.RawLength());
	EXPECT_TRUE(b4.RawAddress() == NULL);
}

TEST(BufferTest, SwapNotEmpty) {
	Buffer b1(16), b2(64);
	b1.SwapWith(b2);
	EXPECT_EQ(64, b1.RawLength());
	EXPECT_EQ(16, b2.RawLength());
}

TEST(BufferTest, SwapSelf) {
	Buffer b1;
	b1.SwapWith(b1);
	EXPECT_EQ(0, b1.RawLength());
	EXPECT_TRUE(b1.RawAddress() == NULL);

	Buffer b2(128);
	b2.SwapWith(b2);
	EXPECT_EQ(128, b2.RawLength());
	EXPECT_TRUE(b2.RawAddress() != NULL);
}

TEST(BufferTest, ResizeZero2Zero) {
	Buffer b;
	EXPECT_TRUE(b.RawResize(0));
	EXPECT_EQ(0, b.RawLength());
	EXPECT_TRUE(b.RawAddress() == NULL);
}

TEST(BufferTest, ResizeZero2Positive) {
	Buffer b;
	EXPECT_TRUE(b.RawResize(1));
	EXPECT_EQ(1, b.RawLength());
	EXPECT_TRUE(b.RawAddress() != NULL);
}

TEST(BufferTest, ResizeZero2Big) {
	Buffer b;
	EXPECT_FALSE(b.RawResize(MAXBSIZE_T));
	EXPECT_EQ(0, b.RawLength());
	EXPECT_TRUE(b.RawAddress() == NULL);
}

TEST(BufferTest, ResizePositive2Zero) {
	Buffer b(1);
	EXPECT_TRUE(b.RawResize(0));
	EXPECT_EQ(0, b.RawLength());
	EXPECT_TRUE(b.RawAddress() == NULL);
}

TEST(BufferTest, ResizePositive2Positive) {
	Buffer b(13);
	EXPECT_TRUE(b.RawResize(33));
	EXPECT_EQ(33, b.RawLength());
	EXPECT_TRUE(b.RawAddress() != NULL);
}

TEST(BufferTest, ResizeBigger) {
	Buffer b(13);
	for (BSIZE_T i = 0; i < b.RawLength(); ++i)
	{
		b.RawAddress()[i] = (char)i;
	}
	EXPECT_TRUE(b.RawResize(23));
	for (BSIZE_T i = 0; i < 13; ++i)
	{
		EXPECT_TRUE(b.RawAddress()[i] == i);
	}
	for (BSIZE_T i = 13; i < b.RawLength(); ++i)
	{
		EXPECT_TRUE(b.RawAddress()[i] == 0);
	}
}

TEST(BufferTest, ResizeSmaller) {
	Buffer b(13);
	for (BSIZE_T i = 0; i < b.RawLength(); ++i)
	{
		b.RawAddress()[i] = (char)i;
	}
	EXPECT_TRUE(b.RawResize(7));
	for (BSIZE_T i = 0; i < b.RawLength(); ++i)
	{
		EXPECT_TRUE(b.RawAddress()[i] == i);
	}
}

TEST(BufferTest, SaveToFile_LoadFromFile) {
	Buffer b1(100);
	Buffer b2;

	Buffer fileName;
	fileName = "c:\\test.txt";
	EXPECT_TRUE(b1.RawSaveToFile(fileName));
	EXPECT_TRUE(b2.RawLoadFromFile(fileName));
	EXPECT_TRUE(b1.RawEquals(b2));
	b1.RawRandomize();
	EXPECT_TRUE(b1.RawSaveToFile(fileName));
	EXPECT_TRUE(b2.RawLoadFromFile(fileName));
	EXPECT_TRUE(b1.RawEquals(b2));

	Buffer errorFileName(5);
	errorFileName.RawRandomize();
	EXPECT_FALSE(b1.RawSaveToFile(errorFileName));
	EXPECT_FALSE(b2.RawLoadFromFile(errorFileName));
}

TEST(BufferTest, Merge) {
	Buffer b1(100);
	Buffer b2(50);
	EXPECT_TRUE(b1.RawMerge(10, b2));
	EXPECT_EQ(100, b1.RawLength());

	Buffer b3(100);
	Buffer b4(50);
	EXPECT_TRUE(b3.RawMerge(60, b4));
	EXPECT_EQ(110, b3.RawLength());

	Buffer b5(100);
	Buffer b6(50);
	EXPECT_TRUE(b5.RawMerge(-10, b6));
	EXPECT_EQ(110, b5.RawLength());

	Buffer b7;
	Buffer b8;
	EXPECT_TRUE(b7.RawMerge(0, b8));
	EXPECT_EQ(0, b7.RawLength());

	Buffer b9;
	Buffer b10;
	EXPECT_TRUE(b9.RawMerge(10, b10));
	EXPECT_EQ(10, b9.RawLength());
}

TEST(BufferTest, Prepend_Append) {
	Buffer b1(100);
	Buffer b2(50);
	EXPECT_TRUE(b1.RawPrepend(b2));
	EXPECT_EQ(150, b1.RawLength());
	EXPECT_TRUE(b1.RawAppend(b2));
	EXPECT_EQ(200, b1.RawLength());

	Buffer b3;
	Buffer b4;
	EXPECT_TRUE(b3.RawPrepend(b4));
	EXPECT_EQ(0, b3.RawLength());
	EXPECT_TRUE(b3.RawAppend(b4));
	EXPECT_EQ(0, b3.RawLength());

	Buffer b5;
	Buffer b6(100);
	EXPECT_TRUE(b5.RawPrepend(b6));
	EXPECT_EQ(100, b5.RawLength());
	EXPECT_TRUE(b5.RawAppend(b6));
	EXPECT_EQ(200, b5.RawLength());
}

TEST(BufferTest, Insert_Remove) {
	Buffer b1(100);
	Buffer b2(50);
	EXPECT_TRUE(b1.RawInsert(50, b2));
	EXPECT_FALSE(b1.RawInsert(1000, b2));
	EXPECT_TRUE(b1.RawRemove(50, 100));
	EXPECT_EQ(50, b1.RawLength());
}

TEST(BufferTest, Reverse) {
	char c1, c2;
	Buffer b1(100);
	b1.RawRandomize();
	Buffer b2 = b1;
	b1.RawReverse();
	b1.RawGet(0, c1);
	b2.RawGet(99, c2);
	EXPECT_EQ(c1, c2);
	b1.RawGet(49, c1);
	b2.RawGet(50, c2);
	EXPECT_EQ(c1, c2);
}
*/