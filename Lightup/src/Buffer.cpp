#include "../include/Lightup.h"
#include <assert.h>

Buffer::Buffer(SIZE_T length)
{
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

Buffer::Buffer()
{

}

Buffer::Buffer(const Buffer& src)
{
	if (src.p != NULL)
	{
		assert(src.len > 0);

		this->p = Buffer::AllocCopy(src.p, src.len);

		// allocate copy can be failed

		if (this->p != NULL)
		{
			this->len = src.len;
		}
	}
}

Buffer::~Buffer()
{
	Buffer::Free(&this->p);
}

SIZE_T Buffer::Length() const
{
	return this->len;
}

char* Buffer::Adress() const
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

char* Buffer::AllocCopy(char* src, SIZE_T length)
{
	if (src == NULL || length <= 0)
	{
		return NULL;
	}
	else
	{
		char* dst = Buffer::Alloc(length);

		// allocate can be failed
		
		if (dst != NULL)
		{
			for (SIZE_T i = 0; i < length; ++i)
			{
				dst[i] = src[i];
			}
			return dst;
		}
		else
		{
			return NULL;
		}
	}
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
