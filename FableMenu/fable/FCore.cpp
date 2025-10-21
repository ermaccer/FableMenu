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

CRGBAFloat::CRGBAFloat(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

CRGBAColour::CRGBAColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

CRGBAColour CRGBAFloat::GetUINTColor()
{
	CRGBAColour result;

	result.R = (unsigned char)(this->R * 255);
	result.G = (unsigned char)(this->G * 255);
	result.B = (unsigned char)(this->B * 255);
	result.A = (unsigned char)(this->A * 255);

	return result;
}


CWideString::CWideString(wchar_t* string)
{ 
	unk = 0;
	str = string;
}

wchar_t* CWideString::GetWideStringData()
{
	return (wchar_t*)**(uintptr_t**)(this);
}

char* CCharString::GetStringData()
{
	return (char*)**(uintptr_t**)(this);
}

CWideString::CWideString()
{
	unk = 0;
	str = nullptr;
}

CDefString::CDefString()
{
	m_nTablePos = 0;
}

CCharString* CDefString::GetString(CCharString* a2, int a3)
{
	return CallMethodAndReturn<CCharString*, 0x9D49B0, CDefString*, CCharString*, int>((CDefString*)0x13CA828, a2, a3);
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

CBaseClass* GameMalloc(unsigned int size)
{
	return CallAndReturn<CBaseClass*, 0xBFEA1A, unsigned int>(size);
}