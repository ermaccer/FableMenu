#pragma once
struct CVector {
	float x, y, z;
};

class CWideString {
	int unk;
	wchar_t* str;

	CWideString(wchar_t*);
};

class CCharString {
public:
	int unk;
	char* str;

	CCharString(char* _str);
};