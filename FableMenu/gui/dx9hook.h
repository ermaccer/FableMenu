#pragma once
#include "../minhook/include/MinHook.h"
#include <d3d9.h>
#include "gui_impl_dx9.h"
#include "log.h"
#include <assert.h>

class DX9Hook {
private:
	DX9Hook();
	~DX9Hook();

	uintptr_t endScenePtr;
	uintptr_t resetPtr;

	uintptr_t endSceneOriginalPtr;
	uintptr_t resetOriginalPtr;

public:
	bool Initialize();
	bool Enable();

	static DX9Hook* Get();

	uintptr_t GetEndSceneAddress();
	uintptr_t GetResetAddress();

	void OnEndScene(LPDIRECT3DDEVICE9 pDevice);
	void OnBeforeReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	void OnAfterReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);

	static HRESULT WINAPI EndScene(LPDIRECT3DDEVICE9 pDevice);
	static HRESULT WINAPI Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
};

DWORD WINAPI DX9Hook_Thread();