#include <Lightup.h>
#include <gtest/gtest.h>

TEST(Guid2StrTest, EmptyConstructor) {
	Guid2Str *o = new Guid2Str();
	EXPECT_TRUE(o->Str() == NULL);
	delete o;
}

TEST(Guid2StrTest, RandomGUID) {
	GUID guid = { 0 };
	UuidCreate(&guid);
	Guid2Str *o = new Guid2Str(guid);
	EXPECT_TRUE(o->Str() != NULL);
	delete o;
}