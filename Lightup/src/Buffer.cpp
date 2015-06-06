#include "../include/Lightup.h"
#include <assert.h>
#include <string>
#include <random>
#include <fstream>
#include <unicode/ucnv.h>

using namespace std;

static default_random_engine random_engine;

#define xchar_encoding "char"
#define xwchar_t_encoding "wchar_T"
#define ModeMustBe(M) if (this->mode != M) return false;
#define VerifyState_RETURN(B) VerifyState(); return B;

Buffer::Buffer(BSIZE_T length)
{
	char* tmp_rawAddress = Buffer::Alloc(length);
	assert(length <= 0 && tmp_rawAddress == NULL);
	// be careful, alloc can be failed
	Construct(Raw, tmp_rawAddress, tmp_rawAddress != NULL ? length : 0, NULL, 0);
}

Buffer::Buffer()
{
	Construct(Raw, NULL, 0, NULL, 0);
}

Buffer::Buffer(const Buffer& src)
{
	Construct(src);
}

Buffer::Buffer(const char* str)
{
	Construct(str);
}

Buffer::Buffer(const wchar_t* str)
{
	Construct(str);
}

Buffer& Buffer::operator=(const Buffer& src)
{
	// be careful, src can be myself
	if (this == &src)
	{
		return *this;
	}

	Destruct();
	Construct(src);
	return *this;
}

Buffer::~Buffer()
{
	Destruct();
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
	Destruct();
	Construct(str);
	return *this;
}

Buffer& Buffer::operator=(const wchar_t* str)
{
	Destruct();
	Construct(str);
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

bool Buffer::_RawReAlloc(BSIZE_T length)
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

bool Buffer::_RawLoadFromFile(const Buffer& fileName)
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
	bool result = this->_RawReAlloc(size);
	if (result)
	{
		in.read(this->rawAddress, size);
	}
	in.close();
	return result;
}

bool Buffer::_RawSaveToFile(const Buffer& fileName)
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

bool Buffer::_RawSet(BSIZE_T pos, char value)
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

bool Buffer::_RawSet(BSIZE_T pos, const Buffer& buff)
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

bool Buffer::_RawRandomize()
{
	if (this->rawAddress != NULL)
	{
		for (BSIZE_T i = 0; i < this->rawLength; ++i)
		{
			this->rawAddress[i] = random_engine();
		}
	}
	return true;
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

void Buffer::SwapWith(Buffer& target)
{
	Mode tmp_mode = target.mode;
	char* tmp_rawAddress = target.rawAddress;
	BSIZE_T tmp_rawLength = target.rawLength;
	char* tmp_strEncoding = target.strEncoding;
	BSIZE_T tmp_strLength = target.strLength;

	target.mode = this->mode;
	target.rawAddress = this->rawAddress;
	target.rawLength = this->rawLength;
	target.strEncoding = this->strEncoding;
	target.strLength = this->strLength;

	this->mode = tmp_mode;
	this->rawAddress = tmp_rawAddress;
	this->rawLength = tmp_rawLength;
	this->strEncoding = tmp_strEncoding;
	this->strLength = tmp_strLength;
}

bool Buffer::_RawResize(BSIZE_T new_len)
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
		if (buff._RawReAlloc(length) == false)
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

bool Buffer::_RawMerge(BSIZE_T pos, const Buffer& buff)
{
	Buffer _this = *this;
	Buffer _buff = buff;
	if (pos < 0) 
	{
		_this.SwapWith(_buff);
		pos = -pos;
	}

	if (_this.rawLength < pos + _buff.rawLength)
	{
		if (!_this._RawResize(pos + _buff.rawLength))
		{
			return false;
		}
	}

	if (_buff.rawLength > 0) 
	{
		if (!_this._RawSet(pos, _buff))
		{
			return false;
		}
	}

	*this = _this;

	return true;
}

bool Buffer::_RawPrepend(const Buffer& buff)
{
	return this->_RawMerge(-buff.rawLength, buff);
}

bool Buffer::_RawAppend(const Buffer& buff)
{
	return this->_RawMerge(this->rawLength, buff);
}

bool Buffer::_RawInsert(BSIZE_T pos, const Buffer& buff)
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
		if (!this->_RawResize(pos))
		{
			return false;
		}
	}
	this->_RawAppend(buff);
	this->_RawAppend(_tail);
	return true;
}

bool Buffer::_RawRemove(BSIZE_T pos, BSIZE_T length)
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
	if (!this->_RawResize(pos))
	{
		return false;
	}
	this->_RawAppend(_tail);
	return true;
}

bool Buffer::_RawReverse()
{
	char temp;
	for (BSIZE_T i = 0; i < this->rawLength / 2; ++i)
	{
		temp = this->rawAddress[i];
		this->rawAddress[i] = this->rawAddress[this->rawLength - 1 - i];
		this->rawAddress[this->rawLength - 1 - i] = temp;
	}
	return true;
}

Buffer& Buffer::_RawView(BSIZE_T pos, BSIZE_T length)
{
	// TODO
	return *this;
}

bool Buffer::StrConvertToEncoding(const char* encoding)
{
	// TODO
	return false;
}

bool Buffer::StrGetEncoding(char*& encoding) const
{
	ModeMustBe(String);
	encoding = this->strEncoding;
	return true;
}

bool Buffer::StrSetEncoding(const char* encoding)
{
	ModeMustBe(String);
	if (this->strEncoding != NULL)
	{
		Buffer::Free(&this->strEncoding);
	}
	this->strEncoding = Buffer::AllocCopy(encoding, strlen(encoding) + 1);
	return true;
}

bool Buffer::isRawMode()
{
	return Raw == this->mode;
}

bool Buffer::toRawMode()
{
	return ConvertMode(Raw);
}

bool Buffer::toStringMode()
{
	return ConvertMode(String);
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

bool Buffer::isStringMode()
{
	return String == this->mode;
}

void Buffer::VerifyState() const
{
	// rawLength can not be negtive
	assert(this->rawLength >= 0);
	// strLength can not be negtive
	assert(this->strLength >= 0);
	// strEncoding can be NULL, but can not be empty string
	assert(this->strEncoding != NULL && strlen(this->strEncoding) > 0);
	// rawAddress is NULL then rawLength must be zero
	// rawAddress is not NULL then rawLength can be zero or positive
	// , zero means empty string, it's ok
	assert(this->rawAddress != NULL ? this->rawLength >= 0 : this->rawLength == 0);
	// if current mode is not string, then strEncoding must be NULL and strLength must be zero
	assert(this->mode != String ? (this->strEncoding == NULL && this->strLength == 0) : true);
}


bool Buffer::_RawCopyFrom(const char* src, BSIZE_T srcOffset, BSIZE_T lengthToCopy, BSIZE_T srcSafeLength, BSIZE_T dstOffset /*= 0*/)
{
	VerifyState();
	if (src == NULL)
	{
		// src is null, nothing to do
		// my state will not change
		// ignore rest arguments
		VerifyState_RETURN(true);
	}

	if (lengthToCopy < 0)
	{
		// lengthToCopy can not be negtive when src is not null
		VerifyState_RETURN(false);
	}
	
	if (lengthToCopy == 0)
	{
		// nothing to copy.
		// my state will not change
		// ignore rest arguments
		VerifyState_RETURN(true);
	}

	// we are going to check src range now,
	// but srcSafeLength can be set to -1 to skip this behaviour
	if (srcSafeLength != -1)
	{
		if (srcSafeLength <= 0)
		{
			// lengthToCopy > 0 && srcSafeLength <= 0
			// invalid arguments
			VerifyState_RETURN(false);
		}

		// lengthToCopy > 0 && srcSafeLength > 0
		// we will check src range now
		bool invalidSrcRange = srcOffset < 0 || srcOffset >= srcSafeLength || (srcOffset + lengthToCopy > srcSafeLength);
		if (invalidSrcRange)
		{
			VerifyState_RETURN(false);
		}
	}

	// check dstOffset
	bool invalidDstOffset = dstOffset < 0 || dstOffset >= this->rawLength || (dstOffset + lengthToCopy > this->rawLength);
	if (invalidDstOffset)
	{
		VerifyState_RETURN(false);
	}

	// ok, it's time to copy
	for (BSIZE_T iSrcOffset = srcOffset, iDstOffset = dstOffset, count = lengthToCopy; count > 0; ++iSrcOffset, ++iDstOffset, --count)
	{
		this->rawAddress[iDstOffset] = src[iSrcOffset];
	}

	// done
	VerifyState_RETURN(true);
}

bool Buffer::_RawCopyFrom(const char* src, BSIZE_T lengthToCopy, BSIZE_T dstOffset /*= 0*/)
{
	return _RawCopyFrom(src, 0, lengthToCopy, -1, dstOffset);
}

bool Buffer::RawCopyTo(char* dst, BSIZE_T dstOffset, BSIZE_T dstSafeLength, BSIZE_T srcOffset, BSIZE_T lengthToCopy) const
{
	VerifyState();

	if (dst == NULL) 
	{
		// dst is null, nothing to do
		// ignore rest arguments
		VerifyState_RETURN(true);
	}

	if (lengthToCopy < 0)
	{
		// invalid arguments
		VerifyState_RETURN(false);
	}

	if (lengthToCopy == 0)
	{
		// dst != NULL && lengthToCopy == 0
		// nothing to do
		// ignore rest arguments
		VerifyState_RETURN(true);
	}

	// we are going to check dst range now,
	// but dstSafeLength can be set to -1 to skip this behaviour
	if (dstSafeLength != -1)
	{
		if (dstSafeLength <= 0)
		{
			// lengthToCopy > 0 && dstSafeLength <= 0
			// invalid arguments
			VerifyState_RETURN(false);
		}

		// lengthToCopy > 0 && dstSafeLength > 0
		// we will check dst range now
		bool invalidDstRange = dstOffset < 0 || dstOffset >= dstSafeLength || (dstOffset + lengthToCopy > dstSafeLength);
		if (invalidDstRange)
		{
			VerifyState_RETURN(false);
		}
	}

	// check srcOffset
	bool invalidSrcOffset = srcOffset < 0 || srcOffset >= this->rawLength || (srcOffset + lengthToCopy > this->rawLength);
	if (invalidSrcOffset)
	{
		VerifyState_RETURN(false);
	}

	// ok, it's time to copy
	for (BSIZE_T iSrcOffset = srcOffset, iDstOffset = dstOffset, count = lengthToCopy; count > 0; ++iSrcOffset, ++iDstOffset, --count)
	{
		dst[iDstOffset] = this->rawAddress[iSrcOffset];
	}

	// done
	VerifyState_RETURN(true);
}

bool Buffer::RawCopyTo(char* dst, BSIZE_T lengthToCopy) const
{
	return RawCopyTo(dst, 0, -1, 0, lengthToCopy);
}

bool Buffer::StrCopyFrom(const char* src, BSIZE_T lengthToCopy, BSIZE_T dstOffset /*= 0*/)
{
	return StrCopyFrom(src, 0, lengthToCopy, -1, dstOffset);
}

bool Buffer::StrCopyFrom(const char* src, BSIZE_T srcOffset, BSIZE_T lengthToCopy, BSIZE_T srcSafeLength, BSIZE_T dstOffset /*= 0*/)
{
	ModeMustBe(String);
	VerifyState();
	// TODO
	return false;
}

bool Buffer::StrCopyFrom(const wchar_t* src, BSIZE_T lengthToCopy, BSIZE_T dstOffset /*= 0*/)
{
	return StrCopyFrom(src, 0, lengthToCopy, -1, dstOffset);
}

bool Buffer::StrCopyFrom(const wchar_t* src, BSIZE_T srcOffset, BSIZE_T lengthToCopy, BSIZE_T srcSafeLength, BSIZE_T dstOffset /*= 0*/)
{
	VerifyState();
	// TODO
	return false;
}

bool Buffer::RawCopyFrom(const char* src, BSIZE_T lengthToCopy, BSIZE_T dstOffset /*= 0*/)
{
	ModeMustBe(Raw);
	return _RawCopyFrom(src, lengthToCopy, dstOffset);
}

bool Buffer::RawCopyFrom(const char* src, BSIZE_T srcOffset, BSIZE_T lengthToCopy, BSIZE_T srcSafeLength, BSIZE_T dstOffset /*= 0*/)
{
	ModeMustBe(Raw);
	return _RawCopyFrom(src, srcOffset, lengthToCopy, srcSafeLength, dstOffset);
}

bool Buffer::RawReAlloc(BSIZE_T length)
{
	ModeMustBe(Raw);
	return _RawReAlloc(length);
}

bool Buffer::RawResize(BSIZE_T length)
{
	ModeMustBe(Raw);
	return _RawResize(length);
}

bool Buffer::RawSet(BSIZE_T pos, char value)
{
	ModeMustBe(Raw);
	return _RawSet(pos, value);
}

bool Buffer::RawSet(BSIZE_T pos, const Buffer& buff)
{
	ModeMustBe(Raw);
	return _RawSet(pos, buff);
}

bool Buffer::RawRandomize()
{
	ModeMustBe(Raw);
	return _RawRandomize();
}

bool Buffer::RawMerge(BSIZE_T pos, const Buffer& buff)
{
	ModeMustBe(Raw);
	return _RawMerge(pos, buff);
}

bool Buffer::RawPrepend(const Buffer& buff)
{
	ModeMustBe(Raw);
	return _RawPrepend(buff);
}

bool Buffer::RawAppend(const Buffer& buff)
{
	ModeMustBe(Raw);
	return _RawAppend(buff);
}

bool Buffer::RawInsert(BSIZE_T pos, const Buffer& buff)
{
	ModeMustBe(Raw);
	return _RawInsert(pos, buff);
}

bool Buffer::RawRemove(BSIZE_T pos, BSIZE_T length)
{
	ModeMustBe(Raw);
	return _RawRemove(pos, length);
}

bool Buffer::RawReverse()
{
	ModeMustBe(Raw);
	return _RawReverse();
}

bool Buffer::RawLoadFromFile(const Buffer& fileName)
{
	ModeMustBe(Raw);
	return _RawLoadFromFile(fileName);
}

bool Buffer::RawSaveToFile(const Buffer& fileName)
{
	ModeMustBe(Raw);
	return _RawSaveToFile(fileName);
}

bool Buffer::_RawClear()
{
	Destruct();
	return true;
}

bool Buffer::StrAddress(char*& value) const
{
	ModeMustBe(String);
	if (StrIsEncoding(xchar_encoding))
	{
		value = this->rawAddress;
		return true;
	}
	else
	{
		return false;
	}
}

bool Buffer::StrAddress(wchar_t*& value) const
{
	ModeMustBe(String);
	if (StrIsEncoding(xwchar_t_encoding))
	{
		value = (wchar_t*)this->rawAddress;
		return true;
	}
	else
	{
		return false;
	}
}

void Buffer::Construct(Mode _mode, char* _rawAddress, BSIZE_T _rawLength, char* _strEncoding, BSIZE_T _strLength)
{
	this->mode = mode;
	this->rawAddress = _rawAddress;
	this->rawLength = _rawLength;
	this->strEncoding = _strEncoding;
	this->strLength = _strLength;
}

void Buffer::Construct(const Buffer& src)
{
	src.VerifyState();
	this->VerifyState();

	char* tmp_rawAddress = NULL;
	if (src.rawAddress != NULL)
	{
		tmp_rawAddress = Buffer::AllocCopy(src.rawAddress, src.rawLength);
		if (tmp_rawAddress == NULL)
		{
			// oops, allocate failed
			// TODO throw exception
			return;
		}
	}

	char* tmp_strEncoding = NULL;
	if (src.strEncoding != NULL)
	{
		tmp_strEncoding = Buffer::AllocCopy(src.strEncoding, strlen(src.strEncoding) + 1);
		if (tmp_strEncoding == NULL)
		{
			// oops, allocate failed
			// don't forget to free tmp_rawAddress
			if (tmp_rawAddress != NULL)
			{
				Buffer::Free(&tmp_rawAddress);
			}

			// TODO throw exception
			return;
		}
	}

	Construct(src.mode, tmp_rawAddress, src.rawLength, tmp_strEncoding, src.strLength);
}

void Buffer::Construct(const char* str)
{
	this->VerifyState();

	char*	tmp_rawAddress = NULL;
	BSIZE_T	tmp_rawLength = 0;
	char*	tmp_strEncoding = NULL;
	BSIZE_T	tmp_strLength = 0;

	if (str != NULL)
	{
		// str can be empty string, it's ok
		tmp_strLength = strlen(str);
		tmp_rawLength = tmp_strLength + 1;
		tmp_rawAddress = Buffer::AllocCopy(str, tmp_rawLength);
		if (tmp_rawAddress == NULL)
		{
			// oops, allocate failed
			// TODO throw exception
			return;
		}
	}

	tmp_strEncoding = Buffer::AllocCopy(xchar_encoding, strlen(xchar_encoding) + 1);
	if (tmp_strEncoding == NULL)
	{
		// oops, allocate failed
		// do not forget to free tmp_rawAddress
		if (tmp_rawAddress != NULL)
		{
			Buffer::Free(&tmp_rawAddress);
		}
		// TODO throw exception
		return;
	}

	Construct(String, tmp_rawAddress, tmp_rawLength, tmp_strEncoding, tmp_strLength);
}

void Buffer::Construct(const wchar_t* str)
{
	this->VerifyState();

	char*	tmp_rawAddress = NULL;
	BSIZE_T	tmp_rawLength = 0;
	char*	tmp_strEncoding = NULL;
	BSIZE_T	tmp_strLength = 0;

	if (str != NULL)
	{
		// str can be empty string, it's ok
		tmp_strLength = wcslen(str);
		tmp_rawLength = tmp_strLength * sizeof(wchar_t) + sizeof(wchar_t);
		tmp_rawAddress = Buffer::AllocCopy((char*)str, tmp_rawLength);
		if (tmp_rawAddress == NULL)
		{
			// oops, allocate failed
			// TODO throw exception
			return;
		}
	}

	tmp_strEncoding = Buffer::AllocCopy(xwchar_t_encoding, strlen(xwchar_t_encoding) + 1);
	if (tmp_strEncoding == NULL)
	{
		// oops, allocate failed
		// do not forget to free tmp_rawAddress
		if (tmp_rawAddress != NULL)
		{
			Buffer::Free(&tmp_rawAddress);
		}
		// TODO throw exception
		return;
	}

	Construct(String, tmp_rawAddress, tmp_rawLength, tmp_strEncoding, tmp_strLength);
}

void Buffer::Destruct()
{
	this->mode = Raw;
	if (this->rawAddress != NULL)
	{
		Buffer::Free(&this->rawAddress);
	}
	this->rawLength = 0;
	if (this->strEncoding != NULL)
	{
		Buffer::Free(&this->strEncoding);
	}
	this->strLength = 0;
}

bool Buffer::StrIsEncoding(const char* encoding) const
{
	ModeMustBe(String);

	if (this->strEncoding == NULL && encoding == NULL)
	{
		return true;
	}
	else if (this->strEncoding != NULL && encoding != NULL)
	{
		// compare string ignore case
		return _stricmp(this->strEncoding, encoding) == 0;
	}
	else
	{
		return false;
	}
}
