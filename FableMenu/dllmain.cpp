// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "eDirectX9Hook.h"
#include "utils/MemoryMgr.h"
#include <iostream>
#include "FableMenu.h"
#include "fable/HUD.h"
#include "fable/GameCamera.h"
#include "eSettingsManager.h"
#include "fable/EngineWeather.h"
#include "eDirectInput8Hook.h"
#include "helper/eMouse.h"
#include "eNotifManager.h"

using namespace Memory::VP;
int GenericTrueReturn() { return 1; }
int GenericFalseReturn() { return 0; }
void GenericDummy() { }


void ImGuiInputWatcher()
{
	while (true)
	{
		eMouse::UpdateMouse();
		Notifications->Update();

		if (eDirectX9Hook::ms_bInit)
		{
			ImGuiIO& io = ImGui::GetIO();
			POINT mPos;
			GetCursorPos(&mPos);
			ScreenToClient(eDirectX9Hook::ms_hWindow, &mPos);
			io.MousePos.x = mPos.x;
			io.MousePos.y = mPos.y;
			io.MouseDown[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
			io.MouseDown[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
			io.MouseDown[2] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;
		}


		Sleep(1);
	}
}



void Init()
{
	SettingsMgr->Init();
#ifdef _DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif // DEBUG

	Notifications->Init();
	TheMenu->Init();
	InjectHook(0x4A5DFB, HookWorldUpdate);
	InjectHook(0x69B7F4, &CGameCameraManager::Update);
	InjectHook(0x69EAEE, HUD::Display);
	Patch(0x1237A00, &CInputProcessCameraLookAround::Update);

	eDirectX9Hook::RegisterHook(0x9BEF60, 0x9BEF67, Method_EndScene);
	eDirectX9Hook::RegisterHook(0x9BFCFA, 0x9BFCFF, Method_Reset);

	if (!(SettingsMgr->iOverwriteConstantFPS == 15))
	{
		static int newUpdate = SettingsMgr->iOverwriteConstantFPS;
		Patch<int>(0x41677B, (int)&newUpdate);
	}

	if (SettingsMgr->bSlowMotionEffectsEverything)
		InjectHook(0x4C9920, GenericTrueReturn, PATCH_JUMP);

	Patch<bool>(0x137544A, SettingsMgr->bUseBuiltInWindowedMode ^ 1);
	Patch<int>(0x137545C, SettingsMgr->iDefaultX);
	Patch<int>(0x1375460, SettingsMgr->iDefaultY);

	InjectHook(0xB5237F, HookEngineWeatherConstructor, PATCH_CALL);	
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		Init();
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ImGuiInputWatcher), nullptr, 0, nullptr);
		DisableThreadLibraryCalls(hMod);
		eDirectInput8Hook::SetModule(hMod);
		break;
	case DLL_PROCESS_DETACH:
		eDirectInput8Hook::Destroy();
		break;
	}
	return TRUE;
}

