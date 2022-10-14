#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(CVector _up, CVector _forward)
{
	up = _up;
	forward = _forward;
	CVector r = forward;
	r.Normalise();
	right = CrossProduct(r, CVector(0, 0, 1));
}

CVector Matrix::GetRotationVector()
{
	CVector result;
	return result;
}

void Matrix::RotateX(float angle)
{
	float sin = sinf(angle);
	float cos = cosf(angle);
}
