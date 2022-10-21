#include "eDirectX9Hook.h"
#include "FableMenu.h"
#include "Fable.h"
#include "utils/MemoryMgr.h"
#include "font.h"
#include "eSettingsManager.h"
#include "eDirectInput8Hook.h"
#include "helper/eMouse.h"
#include "eNotifManager.h"
#include "helper/eKeyboardMan.h"
using namespace Memory::VP;

HWND eDirectX9Hook::ms_hWindow;
WNDPROC eDirectX9Hook::ms_pWndProc;
uintptr_t eDirectX9Hook::ms_pHookJumpEndScene;
uintptr_t eDirectX9Hook::ms_pHookJumpReset; 
bool eDirectX9Hook::ms_bInit;
bool eDirectX9Hook::ms_bShouldReloadFonts;


void eDirectX9Hook::RegisterHook(uintptr_t addr, uintptr_t offset, eMethodType type)
{
	switch (type)
	{
	case Method_EndScene:
		ms_pHookJumpEndScene = offset;
		InjectHook(addr, Hook_EndScene, PATCH_JUMP);
		break;
	case Method_Reset:
		ms_pHookJumpReset = offset;
		InjectHook(addr, Hook_Reset, PATCH_JUMP);
		break;
	default:
		break;
	}
}

void __declspec(naked) eDirectX9Hook::Hook_EndScene()
{
	static LPDIRECT3DDEVICE9 pDevice = 0;
	_asm {
		mov pDevice, eax
		pushad
	}
	EndScene(pDevice);
	_asm {
		popad
		push eax
		call    dword ptr[ecx + 168]
		jmp ms_pHookJumpEndScene
	}
}

void __declspec(naked) eDirectX9Hook::Hook_Reset()
{
	_asm pushad
	ImGui_ImplDX9_InvalidateDeviceObjects();
	_asm {
		popad
		push    ecx
		push    eax
		call    dword ptr[edx + 64]
		pushad
	}
	ImGui_ImplDX9_CreateDeviceObjects();
	_asm { 
		popad
		jmp	ms_pHookJumpReset
	}
}

void eDirectX9Hook::Init()
{
	ms_hWindow = 0;
	ms_pWndProc = 0;
	ms_bInit = false;
	ms_bShouldReloadFonts = false;
}

void eDirectX9Hook::SetImGuiStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowRounding = 6.0f;
	style->ItemSpacing = ImVec2(7, 5.5);
	style->FrameRounding = 2.0f;
	style->FramePadding = ImVec2(6, 4.25);
	style->ButtonTextAlign = {};

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_FrameBg] = ImVec4(0.34f, 0.25f, 0.04f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.70f, 0.55f, 0.22f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.51f, 0.40f, 0.15f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.51f, 0.40f, 0.15f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.65f, 0.32f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.57f, 0.45f, 0.19f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.70f, 0.55f, 0.22f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.51f, 0.40f, 0.15f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.69f, 0.55f, 0.23f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.62f, 0.48f, 0.18f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.51f, 0.40f, 0.15f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.60f, 0.47f, 0.18f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.51f, 0.40f, 0.15f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.50f, 0.39f, 0.13f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.57f, 0.45f, 0.17f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.51f, 0.40f, 0.15f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.70f, 0.54f, 0.20f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.65f, 0.51f, 0.21f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.51f, 0.40f, 0.15f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.70f, 0.55f, 0.22f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.60f, 0.21f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.16f, 0.04f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.42f, 0.32f, 0.03f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.94f, 0.80f, 0.38f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.92f, 0.68f, 0.00f, 1.00f);

	ReloadImGuiFont();

}


void eDirectX9Hook::InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(ms_hWindow);
	ImGui_ImplDX9_Init(pDevice);
	SetImGuiStyle();
}

void eDirectX9Hook::ReloadImGuiFont()
{
	float fontSize = 16.0f;
	ImGuiStyle* style = &ImGui::GetStyle();
	ImGuiIO io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, fontSize * SettingsMgr->fMenuScale);
	io.Fonts->Build();
	ImGui_ImplDX9_InvalidateDeviceObjects();

	if (ms_bShouldReloadFonts)
		ms_bShouldReloadFonts = false;
}


void __stdcall eDirectX9Hook::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!ms_bInit)
	{
		D3DDEVICE_CREATION_PARAMETERS params;
		pDevice->GetCreationParameters(&params);
		ms_hWindow = params.hFocusWindow;
		ms_pWndProc = (WNDPROC)SetWindowLongPtr(ms_hWindow, GWL_WNDPROC, (LONG_PTR)WndProc);
		InitImGui(pDevice);
		ms_bInit = true;
	}

	if (ms_bShouldReloadFonts)
		ReloadImGuiFont();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = false;

	static bool draw = true;
	if (draw)
	{
		Notifications->SetNotificationTime(5500);
		Notifications->PushNotification("FableMenu %s is running! Press %s to open the menu.", FABLEMENU_VERSION, eKeyboardMan::KeyToString(SettingsMgr->iMenuOpenKey));
		draw = false;
	}

#ifdef _DEBUG
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();
	float x = ImGui::GetIO().DisplaySize.x;
	float len = ImGui::CalcTextSize("FableMenu Debug Build").x;
	drawList->AddText({ (x / 2.0f) - (len / 2.0f) ,0 }, IM_COL32(255, 255, 255, 200), "FableMenu Debug Build");
#endif // _DEBUG

	Notifications->Draw();

	TheMenu->Draw();
	TheMenu->Process();

	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}


LRESULT __stdcall eDirectX9Hook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KILLFOCUS:
		TheMenu->m_bIsFocused = false;
		break;
	case WM_SETFOCUS:
		TheMenu->m_bIsFocused = true;
		break;
	case WM_KEYDOWN:
		if (wParam == SettingsMgr->iMenuOpenKey)
			TheMenu->m_bIsActive ^= 1;
		break;
	default:
		break;
	}
	if (TheMenu->m_bIsActive)
		return ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);


	return CallWindowProc(ms_pWndProc, hWnd, uMsg, wParam, lParam);
}
