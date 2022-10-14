#include "FreeCamera.h"
#include "..\Fable.h"
#include "..\helper\eMouse.h"
#include <math.h>
#include <Windows.h>
#include "..\eSettingsManager.h"
#include "..\FableMenu.h"

static float round_angle(float angle)
{
	if (angle < 0.0 || angle >= 1.0)
	{
		angle = fmod(angle, 1.0);
		if (angle < 0.0)
			angle = angle + 1.0;
	}
	return angle;
}

void FreeCamera::Update()
{
	UpdateMovement();
	UpdateRotation();
	TheCamera->pos = TheMenu->camPos;
}

void FreeCamera::UpdateRotation()
{
	float xy = TheCamera->GetXY();
	float yz = TheCamera->GetYZ();

	CVector pos = TheCamera->pos;

	float x_rot = eMouse::GetDeltaX() / 360.0 / 2.0 + xy;

	float y_rot = yz - (eMouse::GetDeltaY() / 360.0 / 2.0);

	x_rot = round_angle(x_rot);
	y_rot = round_angle(y_rot);

	x_rot *= M_PI * 2.0f;
	y_rot *= M_PI * 2.0f;

	CVector newRot;
	float magnitude = 40.0f;

	float cos_yz = cos(y_rot);
	newRot.X = sin(x_rot) * (magnitude * cos_yz);
	newRot.Y = cos(x_rot) * (magnitude * cos_yz);
	newRot.Z = sin(y_rot) * magnitude;

	CVector result = pos + newRot;

	TheCamera->PointAt(&result);
}

void FreeCamera::UpdateMovement()
{
	Matrix matrix = TheCamera->GetMatrix();

	CVector fwd = matrix.forward;
	CVector strafe = matrix.right;
	CVector up = matrix.up;

	if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyForward))
		TheMenu->camPos += fwd * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * 1;
	if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyBack))
		TheMenu->camPos += fwd * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * -1;

	if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyLeft))
		TheMenu->camPos += strafe * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * -1;
	if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRight))
		TheMenu->camPos += strafe * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * 1;

	if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyUp))
		TheMenu->camPos += up * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * 1;
	if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyDown))
		TheMenu->camPos += up * TheMenu->m_fFreeCamSpeed * GetDeltaTime() * -1;
}
