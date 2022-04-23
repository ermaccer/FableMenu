#include "GameCamera.h"
#include "..\FableMenu.h"
#include "..\core.h"

CCamera* mouseLookCam = nullptr;

void CGameCameraManager::Update()
{
	CCamera* cam = (CCamera*)(*(int*)(this + 64) + 4);
	mouseLookCam = cam;

	if (FableMenu::ms_bFreezeCamera || FableMenu::ms_bEnableFreeCamera)
		return;

	CallMethod<0x84DC10, CGameCameraManager*>(this);

}
