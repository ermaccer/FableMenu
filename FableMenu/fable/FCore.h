#pragma once
#include <math.h>


class CVector
{
public:
	float X, Y, Z;
	CVector(void) {}
	CVector(float a, float b, float c)
	{
		X = a;
		Y = b;
		Z = c;
	}
	float Heading(void) const { return atan2(-X, Y); }
	float Magnitude(void) const { return sqrt(X * X + Y * Y + Z * Z); }
	float MagnitudeSqr(void) const { return X * X + Y * Y + Z * Z; }
	float Magnitude2D(void) const { return sqrt(X * X + Y * Y); }
	float MagnitudeSqr2D(void) const { return X * X + Y * Y; }
	void Normalise();

	const CVector& operator+=(CVector const& right) {
		X += right.X;
		Y += right.Y;
		Z += right.Z;
		return *this;
	}

	const CVector& operator+=(float const& right) {
		X += right;
		Y += right;
		Z += right;
		return *this;
	}

	const CVector& operator-=(CVector const& right) {
		X -= right.X;
		Y -= right.Y;
		Z -= right.Z;
		return *this;
	}

	const CVector& operator*=(float right) {
		X *= right;
		Y *= right;
		Z *= right;
		return *this;
	}

	const CVector& operator/=(float right) {
		X /= right;
		Y /= right;
		Z /= right;
		return *this;
	}

	CVector operator-() const {
		return CVector(-X, -Y, -Z);
	}
};

inline CVector operator+(const CVector& left, const CVector& right)
{
	return CVector(left.X + right.X, left.Y + right.Y, left.Z + right.Z);
}

inline CVector operator-(const CVector& left, const CVector& right)
{
	return CVector(left.X - right.X, left.Y - right.Y, left.Z - right.Z);
}

inline CVector operator*(const CVector& left, float right)
{
	return CVector(left.X * right, left.Y * right, left.Z * right);
}

inline CVector operator*(float left, const CVector& right)
{
	return CVector(left * right.X, left * right.Y, left * right.Z);
}

inline CVector operator/(const CVector& left, float right)
{
	return CVector(left.X / right, left.Y / right, left.Z / right);
}

CVector CrossProduct(const CVector& v1, const CVector& v2);
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
	CCharString();
};