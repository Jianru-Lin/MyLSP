#include "../include/Lightup.h"

Buffer::Buffer(SIZE_T length)
{
	this->p = NULL;
	this->len = 0;

	this->p = Buffer::Alloc(length);
	if (this->p != NULL) 
	{
		this->len = length;
	}
	else 
	{
		// this->len will be zero
	}
}

Buffer::~Buffer()
{
	Buffer::Free(&this->p);
}

SIZE_T Buffer::Length()
{
	return this->len;
}

char* Buffer::Adress()
{
	return this->p;
}

char* Buffer::Alloc(SIZE_T length)
{
	if (length == 0) 
	{
		return NULL;
	}

	return (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, length);
}

void Buffer::Free(char** p)
{
	if (p == NULL || *p == NULL) 
	{
		return;
	}
	else
	{
		HeapFree(GetProcessHeap(), 0, *p);
		*p = NULL;
	}
}
