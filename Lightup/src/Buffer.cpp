#include "../include/Lightup.h"
#include <assert.h>
#include <string>
#include <random>
#include <fstream>

using namespace std;

static default_random_engine random_engine;

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

bool Buffer::LoadFromFile(const Buffer& fileName)
{
	if (fileName.p == NULL || fileName.p[fileName.len - 1] != '\0')
	{
		return false;
	}
	ifstream in(fileName.p, ios::in | ios::binary | ios::ate);
	if (!in.is_open())
	{
		return false;
	}
	size_t size = (size_t)in.tellg();
	in.seekg(0, ios::beg);
	bool result = this->ReAlloc(size);
	if (result)
	{
		in.read(this->p, size);
	}
	in.close();
	return result;
}

bool Buffer::SaveToFile(const Buffer& fileName)
{
	if (fileName.p == NULL || fileName.p[fileName.len - 1] != '\0')
	{
		return false;
	}
	ofstream out(fileName.p, ios::out | ios::binary);
	if (!out.is_open())
	{
		return false;
	}
	out.write(this->p, this->len);
	out.close();
	return true;
}

bool Buffer::IsAllBytesZero() const
{
	if (this->p == NULL)
	{
		return true;
	}
	else
	{
		for (SIZE_T i = 0; i < this->len; ++i)
		{
			if (this->p[i] != 0)
			{
				return false;
			}
		}

		return true;
	}
}

bool Buffer::Set(SIZE_T pos, char value)
{
	if (this->p != NULL && pos >= 0 && pos < this->len)
	{
		this->p[pos] = value;
		return true;
	}
	else
	{
		return false;
	}
}

bool Buffer::Get(SIZE_T pos, char& value) const
{
	if (this->p != NULL && pos >= 0 && pos < this->len)
	{
		value = this->p[pos];
		return true;
	}
	else
	{
		return false;
	}
}

void Buffer::Randomize()
{
	if (this->p != NULL)
	{
		for (SIZE_T i = 0; i < this->len; ++i)
		{
			this->p[i] = random_engine();
		}
	}
}

bool Buffer::Equals(const Buffer& target) const
{
	if (target.p == NULL && this->p == NULL)
	{
		return true;
	}
	else if (target.len == this->len)
	{
		// optimize

		if (target.p == this->p)
		{
			return true;
		}

		for (SIZE_T i = 0; i < this->len; ++i)
		{
			if (this->p[i] != target.p[i])
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

void Buffer::Swap(Buffer& target)
{
	char* tmp_p = target.p;
	SIZE_T tmp_len = target.len;
	target.p = this->p;
	target.len = this->len;
	this->p = tmp_p;
	this->len = tmp_len;
}

bool Buffer::Resize(SIZE_T new_len)
{
	if (new_len < 0)
	{
		return false;
	}
	else if (new_len == this->len)
	{
		return true;
	}
	else if (new_len == 0)
	{
		if (this->p != NULL)
		{
			Buffer::Free(&this->p);
			this->len = 0;
		}

		return true;
	}
	else // new_len > 0
	{
		char* new_p = Buffer::Alloc(new_len);
		if (new_p == NULL)
		{
			// current state will not change!
			return false;
		}
		else
		{
			// copy data as needed
			if (this->p != NULL)
			{
				SIZE_T min_len = this->len < new_len ? this->len : new_len;
				for (SIZE_T i = 0; i < min_len; ++i)
				{
					new_p[i] = this->p[i];
				}

				// free resources
				Buffer::Free(&this->p);
			}

			this->p = new_p;
			this->len = new_len;

			return true;
		}
	}
}