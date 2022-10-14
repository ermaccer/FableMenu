#include "FCore.h"
#include "..\core.h"

inline float RecipSqrt(float x, float y) { return x / sqrt(y); }
inline float RecipSqrt(float x) { return RecipSqrt(1.0f, x); }

void CVector::Normalise()
{
	float sq = MagnitudeSqr();
	if (sq > 0.0f) {
		float invsqrt = RecipSqrt(sq);
		X *= invsqrt;
		Y *= invsqrt;
		Z *= invsqrt;
	}
	else
		X = 1.0f;
}

CVector CrossProduct(const CVector& v1, const CVector& v2)
{
	return CVector(v1.Y * v2.Z - v1.Z * v2.Y, v1.Z * v2.X - v1.X * v2.Z, v1.X * v2.Y - v1.Y * v2.X);
}


CWideString::CWideString(wchar_t* string)
{ 
	unk = 0;
	str = string;
}

CCharString::CCharString(char* _str)
{
	CallMethod<0x99EBF0, CCharString*, char*, int>(this, _str, -1);
}

CCharString::CCharString()
{
	unk = 0;
	str = nullptr;
}
