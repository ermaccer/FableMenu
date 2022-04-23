#include "InputProcess.h"
#include "..\FableMenu.h"
DirectInputState* DI_keyState = nullptr;
static CInputProcessControlFreeCamera freeCam;

int DirectInputState::GetDIKeyCode()
{
	return ((int(__thiscall*)(DirectInputState*))0xA03B70)(this);
}

void CInputProcessControlFreeCamera::Update(DirectInputState* keyState, int unk)
{
	((void(__thiscall*)(CInputProcess*, DirectInputState*, int))0x68CB90)(this, keyState, unk);
}

void CInputProcessCameraLookAround::Update(DirectInputState* keyState, int unk)
{
	DI_keyState = keyState;
	if (!FableMenu::ms_bEnableFreeCamera)
		((void(__thiscall*)(CInputProcess*, DirectInputState*, int))0x68D790)(this, keyState, unk);
	else
	{
		if (FableMenu::ms_bEnableFreeCamera)
		{
			if (mouseLookCam)
			{
				freeCam.cam = mouseLookCam;
				freeCam.Update(keyState, unk);
			}
		}


	}
}
