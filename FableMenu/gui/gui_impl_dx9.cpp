#include "gui_impl_dx9.h"

#include "log.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "font.h"

#include "../plugin/Menu.h"
#include "../plugin/Settings.h"
#include "notifications.h"

bool  GUIImplementationDX9::ms_bInit = false;
bool  GUIImplementationDX9::ms_bFailed = false;
bool  GUIImplementationDX9::ms_bShouldReloadFonts = false;
HWND  GUIImplementationDX9::ms_hWindow = 0;
WNDPROC GUIImplementationDX9::ms_pWndProc = 0;


void GUIImplementationDX9::Shutdown()
{
	if (!ms_bInit)
		return;

	ImGui_ImplWin32_Shutdown();
}

bool GUIImplementationDX9::ImGui_Init(LPDIRECT3DDEVICE9 pDevice)
{
	if (!ImGui::CreateContext())
	{
		eLog::Message(__FUNCTION__, "Failed to create ImGui context!");
		return false;
	}

	ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	if (!ImGui_ImplWin32_Init(ms_hWindow))
	{
		eLog::Message(__FUNCTION__, "Failed to init Win32 Backend!");
		return false;
	}
	
	if (!ImGui_ImplDX9_Init(pDevice))
	{
		eLog::Message(__FUNCTION__, "Failed to init DX9 Backend!");
		return false;
	}
	
	ms_pWndProc = (WNDPROC)SetWindowLongPtr(ms_hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
	
	if (!ms_pWndProc)
	{
		eLog::Message(__FUNCTION__, "Failed to set Window Procedure! Error code: %d", GetLastError());
		return false;
	}
	
	ImGui_SetStyle();
	eLog::Message(__FUNCTION__, "INFO: Init OK");
	return true;
}

void GUIImplementationDX9::ImGui_SetStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowRounding = 6.0f;
	style->ItemSpacing = ImVec2(7, 5.5);
	style->FrameRounding = 2.0f;
	style->FramePadding = ImVec2(6, 4.25);
	ImVec4* colors = style->Colors;

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

	ImGui_ReloadFont();
}

void GUIImplementationDX9::ImGui_ReloadFont()
{
	float fontSize = 16.0f;
	float fMenuScale = SettingsMgr->fMenuScale;
	ImGuiStyle* style = &ImGui::GetStyle();
	ImGuiIO io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, fontSize * fMenuScale);
	io.Fonts->Build();

	ImGui_ImplDX9_InvalidateDeviceObjects();

	if (ms_bShouldReloadFonts)
		ms_bShouldReloadFonts = false;
}

void GUIImplementationDX9::OnEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (ms_bFailed)
		return;

	if (!ms_bInit)
		OnEndScene_GUIStart(pDevice);

	ImGui_Process(pDevice);
}

float GUIImplementationDX9::GetDeltaTime()
{
	float delta = 1.0f / 60.0f;
	if (ms_bInit)
		delta = 1.0f / ImGui::GetIO().Framerate;

	return delta;
}

void GUIImplementationDX9::RequestFontReload()
{
	ms_bShouldReloadFonts = true;
}

LRESULT WINAPI GUIImplementationDX9::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			TheMenu->OnActivate();
		break;
	default:
		break;
	}
	if (TheMenu->m_bIsActive)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}


	return CallWindowProc(ms_pWndProc, hWnd, uMsg, wParam, lParam);
}

void GUIImplementationDX9::OnEndScene_GUIStart(LPDIRECT3DDEVICE9 pDevice)
{
	if (ms_bInit)
		return;

	D3DDEVICE_CREATION_PARAMETERS params;
	ZeroMemory(&params, sizeof(D3DDEVICE_CREATION_PARAMETERS));
	pDevice->GetCreationParameters(&params);
	ms_hWindow = params.hFocusWindow;
	ImGui_Init(pDevice);
	ms_bInit = true;
}

void GUIImplementationDX9::ImGui_Process(LPDIRECT3DDEVICE9 pDevice)
{
	if (!ms_bInit)
		return;

	if (ms_bShouldReloadFonts)
		ImGui_ReloadFont();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	GUI_Process();


	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void GUIImplementationDX9::GUI_Process()
{
	ImGui::GetIO().MouseDrawCursor = false;

	static bool ms_bFirstDraw = true;

	if (ms_bFirstDraw)
	{
		Notifications->SetNotificationTime(5500);
		Notifications->PushNotification("FableMenu %s is running! Press %s to open the menu.", FABLEMENU_VERSION, eKeyboardMan::KeyToString(SettingsMgr->iMenuOpenKey));
		ms_bFirstDraw = false;
	}

	Notifications->Draw();
	TheMenu->Draw();
}

void GUIImplementationDX9::OnBeforeReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
}

void GUIImplementationDX9::OnAfterReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_CreateDeviceObjects();
}
