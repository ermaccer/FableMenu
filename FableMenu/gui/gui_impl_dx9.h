#pragma once
#include <d3d9.h>
#include <assert.h>

class GUIImplementationDX9 {
public:
	static bool							ms_bInit;
	static bool							ms_bFailed;
	static bool							ms_bShouldReloadFonts;
	static HWND							ms_hWindow;
	static WNDPROC						ms_pWndProc;

	static void Shutdown();
	static bool ImGui_Init(LPDIRECT3DDEVICE9 pDevice);

	static void ImGui_SetStyle();
	static void	ImGui_ReloadFont();

	static void OnEndScene(LPDIRECT3DDEVICE9 pDevice);
	static void OnEndScene_GUIStart(LPDIRECT3DDEVICE9 pDevice);

	static void ImGui_Process(LPDIRECT3DDEVICE9 pDevice);
	static void GUI_Process();

	static void OnBeforeReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	static void OnAfterReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);


	static float GetDeltaTime();
	static void  RequestFontReload();

	static LRESULT WINAPI WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);