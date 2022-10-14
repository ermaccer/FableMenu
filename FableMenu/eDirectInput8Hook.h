#pragma once
#include <dinput.h>
#include <Windows.h>

typedef long(__stdcall* DIGetDeviceState)(IDirectInputDevice8*, DWORD, LPVOID);
typedef long(__stdcall* DIGetDeviceData)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);

class eDirectInput8Hook {
public:
	static DIGetDeviceState ms_pGetDeviceState;
	static DIGetDeviceData    ms_pGetDeviceData;

	static uintptr_t    ms_pClassInterface;
	static HMODULE      ms_hMod;
	static uintptr_t	ms_pFuncPtrs[2];

	static IDirectInput8* ms_pDirectInput;
	static LPDIRECTINPUTDEVICE8 ms_pDevice;

	static bool ms_bInit;
	
	static void	   SetClassInterface(uintptr_t cI);
	static void    SetModule(HMODULE mod);
	static void	   Init();
	static void	   Destroy();

	static HRESULT WINAPI GetDeviceState_Hook(IDirectInputDevice8* device, DWORD cbData, LPVOID lpvData);
	static HRESULT WINAPI GetDeviceData_Hook(IDirectInputDevice8* device, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod,LPDWORD pdwInOut,DWORD dwFlags);
};