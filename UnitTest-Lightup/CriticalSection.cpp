#include <Lightup.h>
#include <gtest/gtest.h>

TEST(CriticalSectionTest, EnterLeave) {
	CriticalSection cs;
	cs.Enter();
	cs.Leave();
}