#pragma once
class Buffer
{
public:
	Buffer();
	Buffer(SIZE_T length);
	~Buffer();

	// copy constructor & assignment operator
public:
	Buffer(const Buffer& src);
	Buffer& operator=(const Buffer& src);

public:
	SIZE_T	Length()													const;
	char*	Address()													const;
	bool	ReAlloc(SIZE_T length);
	bool	Resize(SIZE_T length);
	bool	IsAllBytesZero()											const;
	bool	Set(SIZE_T pos, char value);
	bool	Get(SIZE_T pos, char& value)								const;
	bool	Set(SIZE_T pos, const Buffer& buff);
	bool	Get(SIZE_T pos, SIZE_T length, Buffer& buff)				const;
	void	Randomize();
	bool	Equals(const Buffer& target)								const;
	void	Swap(Buffer& target);
	bool	Merge(SSIZE_T pos, const Buffer& buff);
	bool	Prepend(const Buffer& buff);
	bool	Append(const Buffer& buff);
	bool	Insert(SIZE_T pos, const Buffer& buff);
	bool	Remove(SIZE_T pos, SIZE_T length);
	void	Reverse();
	Buffer& View(SIZE_T pos, SIZE_T length);

private:
	char* p = NULL;
	SIZE_T len = 0;

	// string utility
public:
	Buffer& operator=(const char* str);
	Buffer& operator=(const wchar_t* str);
	bool CurrentEncoding(Buffer& encoding);
	bool ConvertEncoding(const Buffer& fromEncoding, const Buffer& toEncoding);

	// file system
public:
	bool LoadFromFile(const Buffer& fileName);
	bool SaveToFile(const Buffer& fileName);

public:
	static char* Alloc(SIZE_T length);
	static char* AllocCopy(const char* src, SIZE_T length);
	static void Free(char** p);

};

