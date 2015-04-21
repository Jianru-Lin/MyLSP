#include "../include/Lightup.h"

Buffer::Buffer(SIZE_T length)
{
	this->p = Buffer::Alloc(length);
}

Buffer::~Buffer()
{
	Buffer::Free(&this->p);
}

char* Buffer::Adress()
{
	return this->p;
}

char* Buffer::Alloc(SIZE_T length)
{
	return (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, length);
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
