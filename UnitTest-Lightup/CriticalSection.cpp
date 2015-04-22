#include <Lightup.h>
#include <gtest/gtest.h>

TEST(CriticalSectionTest, EnterLeave) {
	CriticalSection cs;
	cs.Enter();
	cs.Leave();
}

TEST(CriticalSectionTest, NewDelete) {
	CriticalSection *cs = new CriticalSection();
	delete cs;
}

TEST(CriticalSectionTest, EnterDelete) {
	CriticalSection *cs = new CriticalSection();
	cs->Enter();
	delete cs;
}

TEST(CriticalSection, LeaveDelete) {
	CriticalSection *cs = new CriticalSection();
	cs->Leave();
	delete cs;
}