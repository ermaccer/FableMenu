// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "gui/dx9hook.h"
#include "gui/log.h"
#include "gui/notifications.h"

#include "utils/MemoryMgr.h"

#include "fable/HUD.h"
#include "fable/GameCamera.h"
#include "helper/eMouse.h"


#include "plugin/Menu.h"
#include "plugin/Settings.h"

#include <iostream>


using namespace Memory::VP;
int GenericTrueReturn() { return 1; }
int GenericFalseReturn() { return 0; }
void GenericDummy() { }

void PluginProcess()
{
	while (true)
	{
		eMouse::UpdateMouse();
		Notifications->Update();
		TheMenu->Process();
		Sleep(1);
	}
}

void Init()
{
#ifdef _DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif // DEBUG

	Notifications->Init();

	InjectHook(0x4162E3, HookRegularUpdate);
	InjectHook(0x4A5DFB, HookWorldUpdate);
	InjectHook(0x69B7F4, &CGameCameraManager::Update);
	InjectHook(0x69EAEE, HUD::Display);
	Patch(0x1237A00, &CInputProcessCameraLookAround::Update);

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

	// change dinput coop level
	Patch<char>(0xAB5786 + 1, 10);

	CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(PluginProcess), 0, NULL, 0);

	HANDLE h = 0;

	h = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DX9Hook_Thread), 0, NULL, 0);

	if (!(h == nullptr)) CloseHandle(h);
}


extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		eLog::Initialize();
		Init();
	}
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		GUIImplementationDX9::Shutdown();
		break;
	}
	return TRUE;
}
