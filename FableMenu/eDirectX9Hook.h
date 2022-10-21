#include <Windows.h>
#include <d3d9.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "core.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

enum eMethodType {
	Method_EndScene,
	Method_Reset,
	Method_Total
};

class eDirectX9Hook {
public:
	static HWND ms_hWindow;
	static WNDPROC ms_pWndProc;
	static ImGuiStyle	ms_localStyleCopy;

	static uintptr_t ms_pHookJumpEndScene;
	static uintptr_t ms_pHookJumpReset;


	static bool ms_bInit;
	static bool ms_bShouldReloadFonts;

	static void RegisterHook(uintptr_t addr, uintptr_t offset, eMethodType type);

	static void		Hook_EndScene();
	static void		Hook_Reset();


	static void	   Init();
	static void    SetImGuiStyle();
	static void    InitImGui(LPDIRECT3DDEVICE9 pDevice);
	static void	   ReloadImGuiFont();

	static void __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice);	
	static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


};


DWORD WINAPI DirectXHookThread(LPVOID lpReserved);
