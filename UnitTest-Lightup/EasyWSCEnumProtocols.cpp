#include <Lightup.h>
#include <gtest/gtest.h>

TEST(EasyWSCEnumProtocolsTest, NoAction) {
	EasyWSCEnumProtocols enumProtocols;
}

TEST(EasyWSCEnumProtocolsTest, NullInvoke) {
	EasyWSCEnumProtocols enumProtocols;
	EXPECT_TRUE(enumProtocols.Invoke(NULL));
	EXPECT_TRUE(enumProtocols.ProtocolList() != NULL);
	EXPECT_TRUE(enumProtocols.ProtocolListLength() > 0);
}

TEST(EasyWSCEnumProtocolsTest, NewDelete) {
	EasyWSCEnumProtocols *o = new EasyWSCEnumProtocols();
	delete o;
}

TEST(EasyWSCEnumProtocolsTest, NewInvokeDelete) {
	EasyWSCEnumProtocols *o = new EasyWSCEnumProtocols();
	EXPECT_TRUE(o->Invoke(NULL));
	EXPECT_TRUE(o->ProtocolList() != NULL);
	EXPECT_TRUE(o->ProtocolListLength() > 0);
	delete o;
}