#pragma once
#include "..\Fable.h"
#include "Matrix.h"

class CCamera {
public:
	CVector pos;
	CVector up;
	CVector forward;
	bool unk[2];
	int  unk2;

	float FOV;
	float unk3;
	float unk4;

	Matrix GetMatrix();

	float GetXY();
	float GetYZ();

	void PointAt(CVector* pos);
};

class CGameCameraManager {
public:
	void Update();
};

extern CCamera* TheCamera;