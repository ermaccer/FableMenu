#include "dx9hook.h"

DX9Hook::DX9Hook()
{
	resetPtr = 0;
	resetOriginalPtr = 0;
	endScenePtr = 0;
	endSceneOriginalPtr = 0;
}

DX9Hook::~DX9Hook()
{
	MH_DisableHook((void*)resetPtr);
	MH_DisableHook((void*)endScenePtr);
}

bool DX9Hook::Initialize()
{
	eLog::Message(__FUNCTION__, "INFO: Init");
	HWND hWnd = GetDesktopWindow();

	IDirect3D9* d3d9 = nullptr;
	LPDIRECT3DDEVICE9 device = nullptr;


	bool isDX9Loaded = false;
	auto hDX9 = GetModuleHandleW(L"d3d9.dll");
	if (!hDX9)
		hDX9 = LoadLibraryW(L"d3d9.dll");
	else
		isDX9Loaded = true;

	if (!hDX9 && !isDX9Loaded)
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to obtain d3d9.dll! Error code: %d", GetLastError());
		return false;
	}

	auto pDirect3DCreate9 = GetProcAddress(hDX9, "Direct3DCreate9");
	if (pDirect3DCreate9 == NULL)
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to obtain Direct3DCreate9! Error code: %d", GetLastError());
		return false;
	}


	d3d9 = ((IDirect3D9*(WINAPI*)(UINT))(pDirect3DCreate9))(D3D_SDK_VERSION);

	if (!d3d9)
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to create D3D9.");
		return false;
	}


	D3DDISPLAYMODE displayMode;
	ZeroMemory(&displayMode, sizeof(D3DDISPLAYMODE));

	HRESULT hResult = d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

	if (FAILED(hResult))
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to get default display mode. Error code: 0x%X", hResult);
		return false;
	}


	D3DPRESENT_PARAMETERS params;
	ZeroMemory(&params, sizeof(D3DPRESENT_PARAMETERS));

	params.BackBufferFormat = D3DFMT_UNKNOWN;
	params.BackBufferCount = 1;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.MultiSampleQuality = NULL;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = hWnd;
	params.Windowed = TRUE;
	params.EnableAutoDepthStencil = 0;
	params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	params.Flags = NULL;
	params.FullScreen_RefreshRateInHz = 0;
	params.PresentationInterval = 0;

	hResult = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &device);

	if (FAILED(hResult))
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to create D3D9 device. Error code: 0x%X", hResult);
		return false;
	}

	uintptr_t* vTable = *(uintptr_t**)(device);

	if (vTable == nullptr)
	{
		eLog::Message(__FUNCTION__, "ERROR: Could not obtain D3D9 vTable!");
		return false;
	}

	endScenePtr = vTable[42];
	resetPtr = vTable[16];

	eLog::Message(__FUNCTION__, "INFO: D3D9 vTable: 0x%p", vTable);
	eLog::Message(__FUNCTION__, "INFO: D3D9 EndScene: 0x%p", endScenePtr);
	eLog::Message(__FUNCTION__, "INFO: D3D9 Reset: 0x%p", resetPtr);

	assert(resetPtr);
	assert(endScenePtr);


	MH_Initialize();

	d3d9->Release();
	device->Release();
	device = nullptr;
	d3d9 = nullptr;

	eLog::Message(__FUNCTION__, "INFO: Finished");
	return true;
}

bool DX9Hook::Enable()
{
	eLog::Message(__FUNCTION__, "INFO: Init");

	MH_STATUS s = MH_CreateHook((void*)endScenePtr, EndScene, (void**)&endSceneOriginalPtr);

	if (s == MH_OK)
	{
		eLog::Message(__FUNCTION__, "INFO: EndScene hooked!");
		MH_EnableHook((void*)endScenePtr);
	}
	else
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to hook EndScene! Error code: (MH)%d", s);
		return false;
	}

	s = MH_CreateHook((void*)resetPtr, Reset, (void**)&resetOriginalPtr);

	if (s == MH_OK)
	{
		eLog::Message(__FUNCTION__, "INFO: Reset hooked!");
		MH_EnableHook((void*)resetPtr);
	}
	else
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to hook Reset! Error code: (MH)%d", s);
		return false;
	}

	eLog::Message(__FUNCTION__, "INFO: Finished");
	return true;
}

DX9Hook* DX9Hook::Get()
{
	static DX9Hook* gD3D9Hook = nullptr;

	if (gD3D9Hook == nullptr)
		gD3D9Hook = new DX9Hook();

	assert(gD3D9Hook != nullptr);

	return gD3D9Hook;
}

uintptr_t DX9Hook::GetEndSceneAddress()
{
	return endSceneOriginalPtr;
}

uintptr_t DX9Hook::GetResetAddress()
{
	return resetOriginalPtr;
}

void DX9Hook::OnEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	GUIImplementationDX9::OnEndScene(pDevice);
}

void DX9Hook::OnBeforeReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	GUIImplementationDX9::OnBeforeReset(pDevice, pPresentationParameters);
}

void DX9Hook::OnAfterReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	GUIImplementationDX9::OnAfterReset(pDevice, pPresentationParameters);
}

HRESULT __stdcall DX9Hook::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	uintptr_t addr = DX9Hook::Get()->GetEndSceneAddress();
	assert(addr != 0);

	DX9Hook::Get()->OnEndScene(pDevice);

	return ((HRESULT(WINAPI*)(PDIRECT3DDEVICE9))addr)(pDevice);
}

HRESULT __stdcall DX9Hook::Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	uintptr_t addr = DX9Hook::Get()->GetResetAddress();
	assert(addr != 0);

	DX9Hook::Get()->OnBeforeReset(pDevice, pPresentationParameters);
	HRESULT hr = ((HRESULT(WINAPI*)(PDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*))addr)(pDevice, pPresentationParameters);
	DX9Hook::Get()->OnAfterReset(pDevice, pPresentationParameters);
	return hr;
}

DWORD __stdcall DX9Hook_Thread()
{
	if (!DX9Hook::Get()->Initialize())
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to initialize DX9Hook\n");
		return FALSE;
	}

	if (!DX9Hook::Get()->Enable())
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to enable DX9Hook\n");
		return FALSE;
	}

	eLog::Message(__FUNCTION__, "INFO: DX9Hook initialized OK");

	return TRUE;
}
