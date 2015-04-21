#include "../include/Lightup.h"

CriticalSection::CriticalSection()
{
	InitializeCriticalSection(&this->cs);
}

CriticalSection::~CriticalSection()
{
	DeleteCriticalSection(&this->cs);
}

void CriticalSection::Enter()
{
	EnterCriticalSection(&this->cs);
}

void CriticalSection::Leave()
{
	LeaveCriticalSection(&this->cs);
}