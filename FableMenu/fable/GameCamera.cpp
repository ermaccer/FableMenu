#include "GameCamera.h"
#include "..\plugin\Menu.h"
#include "..\core.h"

CCamera* TheCamera = nullptr;

void CGameCameraManager::Update()
{
	CCamera* cam = (CCamera*)(*(int*)(this + 64) + 4);
	TheCamera = cam;

	if (FableMenu::m_bCustomCameraPos && !FableMenu::ms_bFreeCam)
		cam->pos = TheMenu->camPos;
	else
		TheMenu->camPos = cam->pos;

	if (FableMenu::m_bCustomCameraPos || FableMenu::ms_bFreeCam)
		return;

	CallMethod<0x84DC10, CGameCameraManager*>(this);
}

Matrix CCamera::GetMatrix()
{
	return Matrix(up, forward);
}

float CCamera::GetXY()
{
	float v1, v3, result;

	v1 = atan2(this->forward.X, this->forward.Y) * 0.15915494f;
	v3 = v1;
	if (v1 >= 0.0 && v3 < 1.0)
		return v3;
	result = fmod(v3, 1.0);
	if (result < 0.0)
		result = result + 1.0;
	return result;
}

float CCamera::GetYZ()
{
	float v1, v3, result;

	v1 = atan2(this->forward.Z, sqrt(this->forward.X * this->forward.X + this->forward.Y * this->forward.Y)) * 0.15915494f;
	v3 = v1;
	if (v1 >= 0.0 && v3 < 1.0)
		return v3;
	result = fmod(v3, 1.0);
	if (result < 0.0)
		result = result + 1.0;
	return result;
}

void CCamera::PointAt(CVector* pos)
{
	CallMethod<0xA0C2B0, CCamera*, CVector*>(this, pos);
}