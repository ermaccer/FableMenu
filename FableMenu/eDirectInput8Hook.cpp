#include "eDirectInput8Hook.h"
#include "imgui/imgui.h"
#include <iostream>
#include "minhook/include/MinHook.h"
#include "FableMenu.h"
#include "eDirectX9Hook.h"

IDirectInput8* eDirectInput8Hook::ms_pDirectInput;
LPDIRECTINPUTDEVICE8 eDirectInput8Hook::ms_pDevice;
bool eDirectInput8Hook::ms_bInit;
DIGetDeviceState eDirectInput8Hook::ms_pGetDeviceState;
DIGetDeviceData   eDirectInput8Hook::ms_pGetDeviceData;
uintptr_t	eDirectInput8Hook::ms_pFuncPtrs[2] = {};
uintptr_t	eDirectInput8Hook::ms_pClassInterface = 0;
HMODULE      eDirectInput8Hook::ms_hMod;

void eDirectInput8Hook::SetClassInterface(uintptr_t cI)
{
	ms_pClassInterface = cI;
}
void eDirectInput8Hook::SetModule(HMODULE mod)
{
	ms_hMod = mod;
}
void eDirectInput8Hook::Init()
{
	MH_Initialize();
	ms_bInit = false;
	if (!(DirectInput8Create(ms_hMod, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&ms_pDirectInput, NULL) == DI_OK))
	{
		return;
	}

	if (ms_pClassInterface)
	{
		void** vTable = (void**)(*(int*)ms_pClassInterface);
		uintptr_t cCreateDevice = (uintptr_t)vTable[3];
		HRESULT res = ((HRESULT(__stdcall*)(IDirectInput8*, const GUID&, LPDIRECTINPUTDEVICE8*,LPUNKNOWN))cCreateDevice)(ms_pDirectInput, GUID_SysKeyboard, &ms_pDevice, NULL);

		if (!(res == DI_OK))
		{
			ms_pDirectInput->Release();
			ms_pDirectInput = 0;
			return;
		}
	}
	else
	{
		if (!(ms_pDirectInput->CreateDevice(GUID_SysKeyboard, &ms_pDevice, NULL) == DI_OK))
		{
			ms_pDirectInput->Release();
			ms_pDirectInput = 0;
			return;
		}
	}



	void** vTable = (void**)(*(int*)ms_pDevice);
	ms_pFuncPtrs[0] = (uintptr_t)vTable[9];
	ms_pFuncPtrs[1] = (uintptr_t)vTable[10];


	if (MH_CreateHook((void*)ms_pFuncPtrs[0], GetDeviceState_Hook, (LPVOID*)&ms_pGetDeviceState) != MH_OK || MH_EnableHook((void*)ms_pFuncPtrs[0]) != MH_OK)
	{
		return;
	}
	if (MH_CreateHook((void*)ms_pFuncPtrs[1], GetDeviceData_Hook, (LPVOID*)&ms_pGetDeviceData) != MH_OK || MH_EnableHook((void*)ms_pFuncPtrs[1]) != MH_OK)
	{
		return;
	}

	// no longer needed
	ms_pDirectInput->Release();
	ms_pDevice->Release();

	ms_pDirectInput = 0;
	ms_pDevice = 0;
}

void eDirectInput8Hook::Destroy()
{
	MH_DisableHook((void*)ms_pFuncPtrs[0]);
	MH_DisableHook((void*)ms_pFuncPtrs[1]);
}

HRESULT __stdcall eDirectInput8Hook::GetDeviceState_Hook(IDirectInputDevice8* device, DWORD cbData, LPVOID lpvData)
{
	HRESULT orgResult = ms_pGetDeviceState(device, cbData, lpvData);
	return orgResult;
}

HRESULT __stdcall eDirectInput8Hook::GetDeviceData_Hook(IDirectInputDevice8* device, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
	HRESULT orgResult = ms_pGetDeviceData(device, cbObjectData, rgdod, pdwInOut, dwFlags);

	if (TheMenu->m_bIsActive)
	{
		if (rgdod && cbObjectData == 20)
		{
			switch (rgdod->dwOfs)
			{
			case  DIMOFS_Z:
				if (eDirectX9Hook::ms_bInit)
				{
					ImGuiIO& io = ImGui::GetIO();
					int param;
					param = rgdod->dwData;
					if (param < 0)
						io.MouseWheel = -1.0f;
					if (param > 0)
						io.MouseWheel = 1.0f;
				}				
				break;
			default:
				break;
			}

		}			
	}

	return orgResult;
}
