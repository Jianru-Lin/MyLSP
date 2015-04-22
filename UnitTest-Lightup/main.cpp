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