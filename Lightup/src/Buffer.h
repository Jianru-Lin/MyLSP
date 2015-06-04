#pragma once

#define BSIZE_T SSIZE_T
#define MAXBSIZE_T MAXSSIZE_T
#define MINBSIZE_T MINSSIZE_T

/// Make the memory related works easier.
class Buffer
{
public:
	/// Raw mode default constructor, no memory allocated
	Buffer();
	// Raw mode constructor, allocate specified length of memory
	Buffer(BSIZE_T length);
	// destructor
	~Buffer();

	// copy constructor & assignment operator
public:
	// copy constructor
	Buffer(const Buffer& src);
	// assignment operator
	Buffer& operator=(const Buffer& src);

public:
	void Swap(Buffer& target);

public:
	BSIZE_T	RawLength()													const;
	char*	RawAddress()													const;
	bool	RawCopyFrom(const char* src, BSIZE_T lengthToCopy, BSIZE_T dstOffset = 0);
	bool	RawCopyFrom(const char* src, BSIZE_T srcOffset, BSIZE_T lengthToCopy, BSIZE_T srcSafeLength, SIZE_T dstOffset = 0);
	bool	RawCopyTo(const char* dst, BSIZE_T lengthToCopy)					const;
	bool	RawCopyTo(const char* dst, BSIZE_T dstOffset, BSIZE_T dstSafeLength, BSIZE_T srcOffset, BSIZE_T lengthToCopy)	const;
	bool	RawReAlloc(BSIZE_T length);
	bool	RawResize(BSIZE_T length);
	bool	RawIsAllBytesZero()											const;
	bool	RawSet(BSIZE_T pos, char value);
	bool	RawGet(BSIZE_T pos, char& value)								const;
	bool	RawSet(BSIZE_T pos, const Buffer& buff);
	bool	RawGet(BSIZE_T pos, BSIZE_T length, Buffer& buff)				const;
	void	RawRandomize();
	bool	RawEquals(const Buffer& target)								const;
	bool	RawMerge(BSIZE_T pos, const Buffer& buff);
	bool	RawPrepend(const Buffer& buff);
	bool	RawAppend(const Buffer& buff);
	bool	RawInsert(BSIZE_T pos, const Buffer& buff);
	bool	RawRemove(BSIZE_T pos, BSIZE_T length);
	void	RawReverse();
	Buffer& RawView(BSIZE_T pos, BSIZE_T length);

private:
	char* p = NULL;
	BSIZE_T len = 0;

	// string utility
public:
	Buffer(const char* str);
	Buffer(const wchar_t* str);
	Buffer& operator=(const char* str);
	Buffer& operator=(const wchar_t* str);
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
	bool	StrClear();
	bool	StrGet(BSIZE_T pos, char& c);
	bool	StrGet(BSIZE_T pos, wchar_t& c);
	bool	StrSet(BSIZE_T pos, char c);
	bool	StrSet(BSIZE_T pos, wchar_t c);

private:
	char*	strEncoding = NULL;
	BSIZE_T	strLength = 0;

	// file system
public:
	bool LoadFromFile(const Buffer& fileName);
	bool SaveToFile(const Buffer& fileName);

public:
	static char* Alloc(BSIZE_T length);
	static char* AllocCopy(const char* src, BSIZE_T length);
	static void Free(char** p);

	// Mode
public:
	bool	toRawMode();
	bool	isRawMode();
	bool	toNTStringMode();
	bool	isNTStringMode();
	bool	toLBStringMode();
	bool	isLBStringMode();

private:
	enum Mode
	{
		Raw,
		NTString,	// Null Terminated String
		LBString	// Length Based String
	};
	bool ConvertMode(Mode toMode);

private:
	Mode mode = Raw;

private:
	void CheckState()	const;
};

