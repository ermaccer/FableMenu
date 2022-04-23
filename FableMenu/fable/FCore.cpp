#include "FCore.h"
#include "..\core.h"
CWideString::CWideString(wchar_t* string)
{ 
	unk = 0;
	str = string;
}

CCharString::CCharString(char* _str)
{
	CallMethod<0x99EBF0, CCharString*, char*, int>(this, _str, -1);
}
