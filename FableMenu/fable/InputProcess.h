#pragma once
#include "GameCamera.h"
#include "..\Fable.h"

struct CCamera;
class DirectInputState {
public:
	int GetDIKeyCode();
};


extern DirectInputState* DI_keyState;
extern int DI_unk;
class CInputProcess {
public:
};


class CInputProcessControlFreeCamera : public CInputProcess
{
public:
	char pad[40];
	CCamera* cam;

	void Update(DirectInputState* keyState, int unk);
};

class CInputProcessCameraLookAround : public CInputProcess {
public:
	void Update(DirectInputState* keyState, int unk);
};
