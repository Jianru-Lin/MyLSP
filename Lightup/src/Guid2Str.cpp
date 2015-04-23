#include "../include/Lightup.h"

Guid2Str::Guid2Str()
{
}

Guid2Str::Guid2Str(const GUID& v)
{
	UuidToStringW(&v, &this->str);
}

Guid2Str::~Guid2Str()
{
	if (this->str != NULL)
	{
		RpcStringFree(&this->str);
	}
}

RPC_WSTR Guid2Str::Str()
{
	return this->str;
}
