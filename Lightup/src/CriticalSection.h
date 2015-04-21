#pragma once

class CriticalSection
{
public:
	CriticalSection();
	~CriticalSection();
public:
	void Enter();
	void Leave();
private:
	CRITICAL_SECTION cs;
};

