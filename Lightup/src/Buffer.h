#pragma once
class Buffer
{
public:
	Buffer(SIZE_T length);
	~Buffer();

public:
	SIZE_T	Length();
	char*	Adress();

private:
	char* p;

public:
	static char* Alloc(SIZE_T length);
	static void Free(char** p);
};

