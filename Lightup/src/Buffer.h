#pragma once

#define BSIZE_T SSIZE_T
#define MAXBSIZE_T MAXSSIZE_T
#define MINBSIZE_T MINSSIZE_T

/// Make the memory related works easier.
class Buffer
{
	enum Mode
	{
		Raw,
		String
	};

public:
	/// Raw mode default constructor, no memory allocated
	Buffer();
	/// Raw mode constructor, allocate specified length of memory
	Buffer(BSIZE_T length);
	/// String mode constructor, str must be null terminated, encoding name will be "char"
	Buffer(const char* str);
	/// String mode constructor, str must be null terminated, encoding name will be "wchar_t"
	Buffer(const wchar_t* str);
	/// String mode assignment operator, str must be null terminated, encoding name will be "char"
	Buffer& operator=(const char* str);
	/// String mode assignment operator, str must be null terminated, encoding name will be "wchar_t"
	Buffer& operator=(const wchar_t* str);
	/// common copy constructor
	Buffer(const Buffer& src);
	/// common assignment operator
	Buffer& operator=(const Buffer& src);
	/// destructor
	~Buffer();

private:
	// common
	Mode mode = Raw;
	// raw mode
	char* rawAddress = NULL;
	BSIZE_T rawLength = 0;
	// string mode
	char*	strEncoding = NULL;
	BSIZE_T	strLength = 0;

	// Mode
public:
	bool	toRawMode();
	bool	isRawMode();
	bool	toStringMode();
	bool	isStringMode();

private:
	void CheckState()	const;
	bool ConvertMode(Mode toMode);

public:
	/// swap every thing with target
	void	Swap(Buffer& target);
	/// free all the resources used in raw mode, 
	///		won't touch any resources not belongs to raw mode. 
	///		after invoking this->rawAddress will be null and this->rawLength will be zero.
	bool	RawClear();
	/// free all the resources used in string mode
	///		after invoking this.
	bool	StrClear();
	/// free resources and reset state
	void	Clear();

public:
	BSIZE_T	RawLength()													const;
	char*	RawAddress()												const;
	bool	RawCopyFrom(
				const char* src, 
				BSIZE_T lengthToCopy, 
				BSIZE_T dstOffset = 0);
	bool	RawCopyFrom(
				const char* src, 
				BSIZE_T srcOffset, 
				BSIZE_T lengthToCopy, 
				BSIZE_T srcSafeLength, 
				SIZE_T dstOffset = 0);
	bool	RawCopyTo(
				const char* dst, 
				BSIZE_T lengthToCopy)									const;
	bool	RawCopyTo(
				const char* dst, 
				BSIZE_T dstOffset, 
				BSIZE_T dstSafeLength, 
				BSIZE_T srcOffset, 
				BSIZE_T lengthToCopy)									const;
	bool	RawReAlloc(BSIZE_T length);
	bool	RawResize(BSIZE_T length);
	bool	RawIsAllBytesZero()											const;
	bool	RawSet(BSIZE_T pos, char value);
	bool	RawGet(BSIZE_T pos, char& value)							const;
	bool	RawSet(BSIZE_T pos, const Buffer& buff);
	bool	RawGet(BSIZE_T pos, BSIZE_T length, Buffer& buff)			const;
	bool	RawRandomize();
	bool	RawEquals(const Buffer& target)								const;
	bool	RawMerge(BSIZE_T pos, const Buffer& buff);
	bool	RawPrepend(const Buffer& buff);
	bool	RawAppend(const Buffer& buff);
	bool	RawInsert(BSIZE_T pos, const Buffer& buff);
	bool	RawRemove(BSIZE_T pos, BSIZE_T length);
	bool	RawReverse();
	Buffer& RawView(BSIZE_T pos, BSIZE_T length)						const;
	bool	RawLoadFromFile(const Buffer& fileName);
	bool	RawSaveToFile(const Buffer& fileName);

private:
	bool	_RawCopyFrom(
				const char* src,
				BSIZE_T lengthToCopy,
				BSIZE_T dstOffset = 0);
	bool	_RawCopyFrom(
				const char* src,
				BSIZE_T srcOffset,
				BSIZE_T lengthToCopy,
				BSIZE_T srcSafeLength,
				SIZE_T dstOffset = 0);
	bool	_RawReAlloc(BSIZE_T length);
	bool	_RawResize(BSIZE_T length);
	bool	_RawSet(BSIZE_T pos, char value);
	bool	_RawSet(BSIZE_T pos, const Buffer& buff);
	bool	_RawRandomize();
	bool	_RawMerge(BSIZE_T pos, const Buffer& buff);
	bool	_RawPrepend(const Buffer& buff);
	bool	_RawAppend(const Buffer& buff);
	bool	_RawInsert(BSIZE_T pos, const Buffer& buff);
	bool	_RawRemove(BSIZE_T pos, BSIZE_T length);
	bool	_RawReverse();
	Buffer& _RawView(BSIZE_T pos, BSIZE_T length);
	bool	_RawLoadFromFile(const Buffer& fileName);
	bool	_RawSaveToFile(const Buffer& fileName);
	bool	_RawClear();

	// string mode
public:
	bool	StrCopyFrom(
				const char* src,
				BSIZE_T lengthToCopy,
				BSIZE_T dstOffset = 0);
	bool	StrCopyFrom(
				const char* src,
				BSIZE_T srcOffset,
				BSIZE_T lengthToCopy,
				BSIZE_T srcSafeLength,
				SIZE_T dstOffset = 0);
	bool	StrCopyFrom(
				const wchar_t* src,
				BSIZE_T lengthToCopy,
				BSIZE_T dstOffset = 0);
	bool	StrCopyFrom(
				const wchar_t* src,
				BSIZE_T srcOffset,
				BSIZE_T lengthToCopy,
				BSIZE_T srcSafeLength,
				SIZE_T dstOffset = 0);
	bool	StrCopyTo(const char* dst, BSIZE_T lengthToCopy)			const;
	bool	StrCopyTo(
				const char* dst,
				BSIZE_T dstOffset,
				BSIZE_T dstSafeLength,
				BSIZE_T srcOffset,
				BSIZE_T lengthToCopy)									const;
	bool	StrCopyTo(const wchar_t* dst, BSIZE_T lengthToCopy)			const;
	bool	StrCopyTo(
				const wchar_t* dst,
				BSIZE_T dstOffset,
				BSIZE_T dstSafeLength,
				BSIZE_T srcOffset,
				BSIZE_T lengthToCopy)									const;
	bool	StrGetEncoding(Buffer& encoding);
	bool	StrSetEncoding(const Buffer& encoding);
	bool	StrGuessEncoding(const Buffer& encoding);
	bool	StrConvertToEncoding(const Buffer& toEncoding);
	bool	StrLength(BSIZE_T& length);
	bool	StrIsEmpty();
	bool	StrIndexOf(const Buffer& str, BSIZE_T& pos);
	bool	StrMerge(BSIZE_T pos, const Buffer& buff);
	bool	StrPrepend(const Buffer& str);
	bool	StrAppend(const Buffer& str);
	bool	StrInsert(BSIZE_T pos, const Buffer& buff);
	bool	StrRemove(BSIZE_T pos, BSIZE_T length);
	bool	StrReverse();
	bool	StrRandomize(BSIZE_T length);
	bool	StrEquals(const Buffer& target, bool ignoreCase);
	bool	StrGet(BSIZE_T pos, char& c);
	bool	StrGet(BSIZE_T pos, wchar_t& c);
	bool	StrSet(BSIZE_T pos, char c);
	bool	StrSet(BSIZE_T pos, wchar_t c);

private:
	// free this->strEncoding then assign it null
	void	_FreeStrEncoding();

public:
	static char* Alloc(BSIZE_T length);
	static char* AllocCopy(const char* src, BSIZE_T length);
	static void Free(char** p);
};

