#include "eDirectX9Hook.h"
#include "FableMenu.h"
#include "Fable.h"
#include "utils/MemoryMgr.h"
#include "font.h"
#include "eSettingsManager.h"
#include "eDirectInput8Hook.h"
#include "helper/eMouse.h"

using namespace Memory::VP;

EndScene eDirectX9Hook::m_pEndScene;
HWND eDirectX9Hook::ms_hWindow;
WNDPROC eDirectX9Hook::ms_pWndProc;
Reset eDirectX9Hook::m_pReset;

bool eDirectX9Hook::ms_bInit;
bool eDirectX9Hook::ms_bShouldReloadFonts;

void eDirectX9Hook::Init()
{
	m_pEndScene = 0;
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


long __stdcall eDirectX9Hook::EndScene(LPDIRECT3DDEVICE9 pDevice)
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

	if (TheMenu->m_bIsActive)
	{
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::GetIO().MouseDrawCursor = true;


		TheMenu->Draw();
		TheMenu->Process();

		ImGui::EndFrame();

		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	return m_pEndScene(pDevice);
}

long __stdcall eDirectX9Hook::Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = m_pReset(pDevice, pPresentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();
	return hr;

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
		if (wParam == SettingsMgr->iMenuOpenKey && InGame())
			TheMenu->m_bIsActive ^= 1;
		break;
	default:
		break;
	}
	if (TheMenu->m_bIsActive)
		return ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);


	return CallWindowProc(ms_pWndProc, hWnd, uMsg, wParam, lParam);
}

IDirect3D9* __stdcall eDirectX9Hook::Direct3DCreate9_Hook(UINT SDKVersion)
{
	IDirect3D9* device = Direct3DCreate9(SDKVersion);
	CreateThread(nullptr, 0, DirectXHookThread, nullptr, 0, nullptr);
	eDirectInput8Hook::Init();
	return device;
}


DWORD WINAPI DirectXHookThread(LPVOID lpReserved)
{
	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)&eDirectX9Hook::m_pEndScene, eDirectX9Hook::EndScene);
			kiero::bind(16, (void**)&eDirectX9Hook::m_pReset, eDirectX9Hook::Reset);
			attached = true;
		}
	} while (!attached);
	return TRUE;
}