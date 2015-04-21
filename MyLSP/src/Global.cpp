#include "Global.h"

Global g;

Global::Global()
{
}


Global::~Global()
{
}

int Global::GetRefCount()
{
	return this->refCount;
}

void Global::IncRefCount()
{
	++this->refCount;
}

void Global::DecRefCount()
{
	--this->refCount;
}

void Global::Enter()
{
	this->cs.Enter();
}

void Global::Leave()
{
	this->cs.Leave();
}

WSPUPCALLTABLE Global::GetUpcallTable()
{
	return this->upcallTable;
}

void Global::SetUpcallTable(WSPUPCALLTABLE v)
{
	this->upcallTable = v;
}