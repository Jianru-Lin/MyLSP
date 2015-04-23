#pragma once
class Guid2Str
{
public:
	Guid2Str();
	Guid2Str(const GUID& v);
	~Guid2Str();

public:
	RPC_WSTR Str();

private:
	RPC_WSTR str = NULL;
};

