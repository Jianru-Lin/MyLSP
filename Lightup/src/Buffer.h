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
	/// LBString mode constructor with default encoding
	Buffer(const char* p, BSIZE_T length);
	Buffer(BSIZE_T length);
	~Buffer();

	// copy constructor & assignment operator
public:
	Buffer(const Buffer& src);
	Buffer& operator=(const Buffer& src);

public:
	BSIZE_T	Length()													const;
	char*	Address()													const;
	bool	ReAlloc(BSIZE_T length);
	bool	Resize(BSIZE_T length);
	bool	IsAllBytesZero()											const;
	bool	Set(BSIZE_T pos, char value);
	bool	Get(BSIZE_T pos, char& value)								const;
	bool	Set(BSIZE_T pos, const Buffer& buff);
	bool	Get(BSIZE_T pos, BSIZE_T length, Buffer& buff)				const;
	void	Randomize();
	bool	Equals(const Buffer& target)								const;
	void	Swap(Buffer& target);
	bool	Merge(BSIZE_T pos, const Buffer& buff);
	bool	Prepend(const Buffer& buff);
	bool	Append(const Buffer& buff);
	bool	Insert(BSIZE_T pos, const Buffer& buff);
	bool	Remove(BSIZE_T pos, BSIZE_T length);
	void	Reverse();
	Buffer& View(BSIZE_T pos, BSIZE_T length);

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
	void CheckState();
};

