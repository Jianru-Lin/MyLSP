#pragma once
#include <Lightup.h>

class Global
{
public:
	Global();
	~Global();

	// 引用计数
	// 用于平衡 WSPStartup() 和 WSPCleanup() 调用
public:
	int GetRefCount();
	void IncRefCount();
	void DecRefCount();
private:
	int refCount;

	// 全局临界区
public:
	void Enter();
	void Leave();
private:
	CriticalSection cs;

	// 上调例程表
public:
	WSPUPCALLTABLE GetUpcallTable();
	void SetUpcallTable(WSPUPCALLTABLE v);
private:
	WSPUPCALLTABLE upcallTable;
};

extern Global g;