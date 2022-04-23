#pragma once
#include "..\Fable.h"


struct CCamera {
	CVector pos;
	// matrix or quat? dunno
	char rot[24];
	bool unk[2];
	int  unk2;

	float FOV;
	float unk3;
	float unk4;
};

class CGameCameraManager {
public:
	void Update();
};

extern CCamera* mouseLookCam;