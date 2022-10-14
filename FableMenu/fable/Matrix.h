#pragma once
#include "FCore.h"


class Matrix {
public:
	union {
		struct {
			CVector up;
			float pad;
			CVector right;
			float _pad;
			CVector forward;
			float __pad;
			float mat[4];
		};
		struct
		{
			float M[4][4];
		};
	};

	Matrix();
	Matrix(CVector, CVector);

	CVector GetRotationVector();

	void RotateX(float angle);

};
