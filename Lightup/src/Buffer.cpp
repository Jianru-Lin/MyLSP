#include "../include/Lightup.h"
#include <assert.h>
#include <string>

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

Buffer& Buffer::operator=(const Buffer& src)
{
	const Buffer* p_src = &src;
	if (p_src == this)
	{
		return *this;
	}
	else
	{
		this->p = Buffer::AllocCopy(src.p, src.len);
		this->len = src.len;
		return *this;
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

char* Buffer::Address() const
{
	return this->p;
}

Buffer& Buffer::operator=(const char* str)
{
	if (this->p != NULL)
	{
		Buffer::Free(&this->p);
		this->len = 0;
	}

	if (str != NULL)
	{
		size_t str_len = strlen(str);
		this->p = Buffer::AllocCopy(str, str_len + 1);
		this->len = str_len + 1;
	}

	return *this;
}

Buffer& Buffer::operator=(const wchar_t* str)
{
	if (this->p != NULL)
	{
		Buffer::Free(&this->p);
		this->len = 0;
	}

	if (str != NULL)
	{
		size_t str_len = wcslen(str);
		size_t buff_len = str_len * sizeof(wchar_t) + sizeof(wchar_t);
		this->p = Buffer::AllocCopy((char*)str, buff_len);
		this->len = buff_len;
	}

	return *this;
}

char* Buffer::Alloc(SIZE_T length)
{
	if (length == 0) 
	{
		return NULL;
	}

	return (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, length);
}

char* Buffer::AllocCopy(const char* src, SIZE_T length)
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

bool Buffer::ReAlloc(SIZE_T length)
{
	if (this->p != NULL)
	{
		Buffer::Free(&this->p);
		this->len = 0;
	}

	if (length < 0)
	{
		return false;
	}
	else if (length == 0)
	{
		return true;
	}
	else
	{
		this->p = Buffer::Alloc(length);
		if (this->p != NULL)
		{
			this->len = length;
			return true;
		}
		else
		{
			this->len = 0;
			return false;
		}
	}
}
