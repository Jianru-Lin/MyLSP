#include "../include/Lightup.h"
#include <assert.h>
#include <string>
#include <random>
#include <fstream>
#include <unicode/ucnv.h>

using namespace std;

static default_random_engine random_engine;

Buffer::Buffer(BSIZE_T length)
{
	CheckState();

	this->rawAddress = Buffer::Alloc(length);
	// be careful, alloc can be failed
	if (this->rawAddress != NULL) 
	{
		this->rawLength = length;
	}

	CheckState();
}

Buffer::Buffer()
{
	CheckState();
}

Buffer::Buffer(const Buffer& src)
{
	CheckState();

	if (src.rawAddress != NULL)
	{
		this->rawAddress = Buffer::AllocCopy(src.rawAddress, src.rawLength);

		// allocate copy can be failed

		if (this->rawAddress != NULL)
		{
			this->rawLength = src.rawLength;
		}
	}

	CheckState();
}

Buffer::Buffer(const char* str)
{
	CheckState();

	if (str == NULL)
	{
		this->rawAddress = NULL;
		this->rawLength = 0;
	}
	else
	{
		this->rawLength = strlen(str) + 1;
		this->rawAddress = Buffer::AllocCopy(str, this->rawLength);
	}

	CheckState();
}

Buffer::Buffer(const wchar_t* str)
{
	CheckState();

	if (str == NULL)
	{
		this->rawAddress = NULL;
		this->rawLength = 0;
	}
	else
	{
		this->rawLength = wcslen(str) * sizeof(wchar_t) + sizeof(wchar_t);
		this->rawAddress = Buffer::AllocCopy((char*)str, this->rawLength);
	}

	CheckState();
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
		this->rawAddress = Buffer::AllocCopy(src.rawAddress, src.rawLength);
		this->rawLength = src.rawLength;
		return *this;
	}
}

Buffer::~Buffer()
{
	Buffer::Free(&this->rawAddress);
}

BSIZE_T Buffer::RawLength() const
{
	return this->rawLength;
}

char* Buffer::RawAddress() const
{
	return this->rawAddress;
}

Buffer& Buffer::operator=(const char* str)
{
	if (this->rawAddress != NULL)
	{
		Buffer::Free(&this->rawAddress);
		this->rawLength = 0;
	}

	if (str != NULL)
	{
		size_t str_len = strlen(str);
		this->rawAddress = Buffer::AllocCopy(str, str_len + 1);
		this->rawLength = str_len + 1;
	}

	return *this;
}

Buffer& Buffer::operator=(const wchar_t* str)
{
	if (this->rawAddress != NULL)
	{
		Buffer::Free(&this->rawAddress);
		this->rawLength = 0;
	}

	if (str != NULL)
	{
		size_t str_len = wcslen(str);
		size_t buff_len = str_len * sizeof(wchar_t) + sizeof(wchar_t);
		this->rawAddress = Buffer::AllocCopy((char*)str, buff_len);
		this->rawLength = buff_len;
	}

	return *this;
}

char* Buffer::Alloc(BSIZE_T length)
{
	if (length == 0) 
	{
		return NULL;
	}

	return (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, length);
}

char* Buffer::AllocCopy(const char* src, BSIZE_T length)
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
			for (BSIZE_T i = 0; i < length; ++i)
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

bool Buffer::RawReAlloc(BSIZE_T length)
{
	if (this->rawAddress != NULL)
	{
		Buffer::Free(&this->rawAddress);
		this->rawLength = 0;
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
		this->rawAddress = Buffer::Alloc(length);
		if (this->rawAddress != NULL)
		{
			this->rawLength = length;
			return true;
		}
		else
		{
			this->rawLength = 0;
			return false;
		}
	}
}

bool Buffer::RawLoadFromFile(const Buffer& fileName)
{
	if (fileName.rawAddress == NULL || fileName.rawAddress[fileName.rawLength - 1] != '\0')
	{
		return false;
	}
	ifstream in(fileName.rawAddress, ios::in | ios::binary | ios::ate);
	if (!in.is_open())
	{
		return false;
	}
	size_t size = (size_t)in.tellg();
	in.seekg(0, ios::beg);
	bool result = this->RawReAlloc(size);
	if (result)
	{
		in.read(this->rawAddress, size);
	}
	in.close();
	return result;
}

bool Buffer::RawSaveToFile(const Buffer& fileName)
{
	if (fileName.rawAddress == NULL || fileName.rawAddress[fileName.rawLength - 1] != '\0')
	{
		return false;
	}
	ofstream out(fileName.rawAddress, ios::out | ios::binary);
	if (!out.is_open())
	{
		return false;
	}
	out.write(this->rawAddress, this->rawLength);
	out.close();
	return true;
}

bool Buffer::RawIsAllBytesZero() const
{
	if (this->rawAddress == NULL)
	{
		return true;
	}
	else
	{
		for (BSIZE_T i = 0; i < this->rawLength; ++i)
		{
			if (this->rawAddress[i] != 0)
			{
				return false;
			}
		}

		return true;
	}
}

bool Buffer::RawSet(BSIZE_T pos, char value)
{
	if (this->rawAddress != NULL && pos >= 0 && pos < this->rawLength)
	{
		this->rawAddress[pos] = value;
		return true;
	}
	else
	{
		return false;
	}
}

bool Buffer::RawSet(BSIZE_T pos, const Buffer& buff)
{
	// notice: buff.len can not be zero, so it's impossible to set an empty buff

	if (!(pos >= 0 && pos < this->rawLength) || !(buff.rawLength > 0 && (pos + buff.rawLength) <= this->rawLength))
	{
		return false;
	}
	else
	{
		for (BSIZE_T i = pos, end = pos + buff.rawLength; i < end; ++i)
		{
			this->rawAddress[i] = buff.rawAddress[i];
		}
		return true;
	}
}

bool Buffer::RawGet(BSIZE_T pos, char& value) const
{
	if (this->rawAddress != NULL && pos >= 0 && pos < this->rawLength)
	{
		value = this->rawAddress[pos];
		return true;
	}
	else
	{
		return false;
	}
}

void Buffer::RawRandomize()
{
	if (this->rawAddress != NULL)
	{
		for (BSIZE_T i = 0; i < this->rawLength; ++i)
		{
			this->rawAddress[i] = random_engine();
		}
	}
}

bool Buffer::RawEquals(const Buffer& target) const
{
	if (target.rawAddress == NULL && this->rawAddress == NULL)
	{
		return true;
	}
	else if (target.rawLength == this->rawLength)
	{
		// optimize

		if (target.rawAddress == this->rawAddress)
		{
			return true;
		}

		for (BSIZE_T i = 0; i < this->rawLength; ++i)
		{
			if (this->rawAddress[i] != target.rawAddress[i])
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
	char* tmp_p = target.rawAddress;
	BSIZE_T tmp_len = target.rawLength;
	target.rawAddress = this->rawAddress;
	target.rawLength = this->rawLength;
	this->rawAddress = tmp_p;
	this->rawLength = tmp_len;
}

bool Buffer::RawResize(BSIZE_T new_len)
{
	if (new_len < 0)
	{
		return false;
	}
	else if (new_len == this->rawLength)
	{
		return true;
	}
	else if (new_len == 0)
	{
		if (this->rawAddress != NULL)
		{
			Buffer::Free(&this->rawAddress);
			this->rawLength = 0;
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
			if (this->rawAddress != NULL)
			{
				BSIZE_T min_len = this->rawLength < new_len ? this->rawLength : new_len;
				for (BSIZE_T i = 0; i < min_len; ++i)
				{
					new_p[i] = this->rawAddress[i];
				}

				// free resources
				Buffer::Free(&this->rawAddress);
			}

			this->rawAddress = new_p;
			this->rawLength = new_len;

			return true;
		}
	}
}

bool Buffer::RawGet(BSIZE_T pos, BSIZE_T length, Buffer& buff) const
{
	// notice: length can not be zero, so it's impossible to get an empty buff

	if (!(pos >= 0 && pos < this->rawLength) || !(length > 0 && (length + pos) <= this->rawLength))
	{
		return false;
	}
	else
	{
		if (buff.RawReAlloc(length) == false)
		{
			return false;
		}
		else
		{
			for (BSIZE_T i = 0; i < length; ++i)
			{
				buff.rawAddress[i] = this->rawAddress[i + pos];
			}
			return true;
		}
	}
}

bool Buffer::RawMerge(BSIZE_T pos, const Buffer& buff)
{
	Buffer _this = *this;
	Buffer _buff = buff;
	if (pos < 0) 
	{
		_this.Swap(_buff);
		pos = -pos;
	}

	if (_this.rawLength < pos + _buff.rawLength)
	{
		if (!_this.RawResize(pos + _buff.rawLength))
		{
			return false;
		}
	}

	if (_buff.rawLength > 0) 
	{
		if (!_this.RawSet(pos, _buff))
		{
			return false;
		}
	}

	*this = _this;

	return true;
}

bool Buffer::RawPrepend(const Buffer& buff)
{
	return this->RawMerge(-buff.rawLength, buff);
}

bool Buffer::RawAppend(const Buffer& buff)
{
	return this->RawMerge(this->rawLength, buff);
}

bool Buffer::RawInsert(BSIZE_T pos, const Buffer& buff)
{
	if (pos > this->rawLength)
	{
		return false;
		//pos = this->len;
	}

	Buffer _tail;
	if (this->rawLength > pos)
	{
		if (!this->RawGet(pos, this->rawLength - pos, _tail))
		{
			return false;
		}
		if (!this->RawResize(pos))
		{
			return false;
		}
	}
	this->RawAppend(buff);
	this->RawAppend(_tail);
	return true;
}

bool Buffer::RawRemove(BSIZE_T pos, BSIZE_T length)
{
	if (pos >= this->rawLength || length == 0)
	{
		return false;
	}

	Buffer _tail;
	if (this->rawLength > pos + length)
	{
		if (!this->RawGet(pos + length, this->rawLength - pos - length, _tail))
		{
			return false;
		}
	}
	if (!this->RawResize(pos))
	{
		return false;
	}
	this->RawAppend(_tail);
	return true;
}

void Buffer::RawReverse()
{
	char temp;
	for (BSIZE_T i = 0; i < this->rawLength / 2; ++i)
	{
		temp = this->rawAddress[i];
		this->rawAddress[i] = this->rawAddress[this->rawLength - 1 - i];
		this->rawAddress[this->rawLength - 1 - i] = temp;
	}
}

Buffer& Buffer::RawView(BSIZE_T pos, BSIZE_T length)
{
	// TODO
	return *this;
}

bool Buffer::StrConvertToEncoding(const Buffer& toEncoding)
{
	assert(&toEncoding != this);
	// TODO
	return false;
}

bool Buffer::StrGetEncoding(Buffer& encoding)
{
	return false;
}

bool Buffer::StrSetEncoding(const Buffer& encoding)
{
	return false;
}

bool Buffer::isRawMode()
{
	return Raw == this->mode;
}

bool Buffer::toRawMode()
{
	return ConvertMode(Raw);
}

bool Buffer::toNTStringMode()
{
	return ConvertMode(NTString);
}

bool Buffer::ConvertMode(Mode toMode)
{
	if (toMode == this->mode) {
		return true;
	}
	else if (toMode == Raw) {
		// any mode convert to raw mode is ok
		this->mode = Raw;
		return true;
	}
	else {
		// TODO
		return false;
	}
}

bool Buffer::isNTStringMode()
{
	return NTString == this->mode;
}

bool Buffer::toLBStringMode()
{
	return ConvertMode(LBString);
}

bool Buffer::isLBStringMode()
{
	return LBString == this->mode;
}

void Buffer::CheckState() const
{
	assert(this->rawAddress != NULL ? this->rawLength > 0 : this->rawLength == 0);
}


bool Buffer::RawCopyFrom(const char* src, BSIZE_T srcOffset, BSIZE_T lengthToCopy, BSIZE_T srcSafeLength, SIZE_T dstOffset /*= 0*/)
{
	CheckState();

	// TODO

	CheckState();
	return false;
}

bool Buffer::RawCopyFrom(const char* src, BSIZE_T lengthToCopy, BSIZE_T dstOffset /*= 0*/)
{
	return RawCopyFrom(src, 0, lengthToCopy, -1, dstOffset);
}

bool Buffer::RawCopyTo(const char* dst, BSIZE_T dstOffset, BSIZE_T dstSafeLength, BSIZE_T srcOffset, BSIZE_T lengthToCopy) const
{
	CheckState();
	// TODO
	CheckState();
	return false;
}

bool Buffer::RawCopyTo(const char* dst, BSIZE_T lengthToCopy) const
{
	return RawCopyTo(dst, 0, -1, 0, lengthToCopy);
}
