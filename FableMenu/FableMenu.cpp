#include "imgui/imgui.h"
#include "IniReader.h"
#include <iostream>
#include <Windows.h>
#include "FableMenu.h"
#include "Fable.h"
#include "eDirectX9Hook.h"
#include "utils/MemoryMgr.h"
#include "helper/eKeyboardMan.h"
#include "eSettingsManager.h"
#include "helper/eMouse.h"
#include "plugin/FreeCamera.h"

using namespace Memory::VP;

FableMenu* TheMenu = new FableMenu();

bool FableMenu::ms_bFreeCam = false;
bool FableMenu::m_bCustomCameraPos = false;
bool FableMenu::ms_bDisableHUD = false;
bool FableMenu::m_bCustomCameraFOV = false;
bool FableMenu::ms_bChangeTime = false;
float FableMenu::m_fTime = 0.0f;

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

}

const char* szFactions[] = {
	"FACTION_HERO",
	"FACTION_VILLAGERS",
	"FACTION_BANDITS",
	"FACTION_NEUTRALS",
	"FACTION_TWINBLADE_CAMP_BANDITS",
	"FACTION_MONSTERS",
	"FACTION_GUILD_APPRENTICES_GOOD",
	"FACTION_GUILD_SERVANTS",
	"FACTION_BANDITS_FRIENDLY",
	"FACTION_VILLAGER",
	"FACTION_GUARDS_ENEMY",
	"FACTION_BANDIT",
	"FACTION_BODYGUARD",
	"FACTION_SCRIPT_NEUTRAL",
	"FACTION_NEUTRAL",
	"FACTION_MAP_KEEPER",
	"FACTION_PRISONER",
	"FACTION_PRISON_GUARD",
	"FACTION_TRADERS",
	"FACTION_PICNIC_AREA",
	"FACTION_GUILD",
	"FACTION_MONSTER",
};

void FableMenu::Init()
{
	sprintf(szFactionName, szFactions[0]);
}

void FableMenu::Draw()
{
	if (!m_bIsActive)
		return;


	ImGui::Begin("FableMenu by ermaccer", &m_bIsActive, ImGuiWindowFlags_MenuBar);
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Settings"))
			{
				m_bSubmenuActive[SUBMENU_SETTINGS] = true;
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		if (CMainGameComponent::Get())
		{
			if (ImGui::BeginTabBar("##tabs"))
			{
				if (ImGui::BeginTabItem("Player"))
				{
					DrawPlayerTab();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Camera"))
				{
					DrawCameraTab();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("World"))
				{
					DrawWorldTab();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Misc."))
				{
					DrawMiscTab();
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
		else
			ImGui::TextWrapped("Not ready!");
	}
	ImGui::End();

	if (m_bSubmenuActive[SUBMENU_SETTINGS])
		DrawSettings();
}

void FableMenu::Process()
{
	if (m_bCustomCameraFOV)
	{
		Nop(0xA0BEE2, 3);
	}
	else
	{
		//89 41 2C 
		Patch<char>(0xA0BEE2, 0x89);
		Patch<char>(0xA0BEE2 + 1, 0x41);
		Patch<char>(0xA0BEE2 + 2, 0x2C);
	}

	if (ms_bChangeTime)
	{
		Nop(0x6BBA58, 3);
	}
	else
	{
		//D9 56 08 
		Patch<char>(0x6BBA58, 0xD9);
		Patch<char>(0x6BBA58 + 1, 0x56);
		Patch<char>(0x6BBA58 + 2, 0x08);
	}
}

void FableMenu::DrawPlayerTab()
{
	CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetPlayer();
	if (plr)
	{
		CThing* t = plr->GetCharacterThing();
		CTCHeroStats* stats = t->GetHeroStats();
		CTCHeroMorph* morph = t->GetHeroMorph();
		CTCHeroExperience* exp = t->GetHeroExperience();
		CTCHero* hero = t->GetHero();
		if (stats)
		{
			if (ImGui::CollapsingHeader("Data"))
			{
				ImGui::InputFloat("Health", &t->m_fHealth);
				ImGui::InputFloat("Max. Health", &t->m_fMaxHealth);
				ImGui::InputInt("Will##data", &stats->m_nWillPower, 0);
				ImGui::InputInt("Max. Will", &stats->m_nMaxWillPower, 0);
				ImGui::InputInt("Gold", &stats->m_nGold);
				ImGui::InputFloat("Age", &stats->m_fAge);
				if (hero)
				{
					ImGui::Checkbox("Can Use Weapons", &hero->m_bCanUseWeapons);
					ImGui::Checkbox("Can Use Will", &hero->m_bCanUseWill);
				}
				if (exp)
				{
					ImGui::Separator();
					ImGui::Text("Experience");
					ImGui::Separator();
					ImGui::InputInt("General##exp", &exp->m_nGeneralExperience, 0);
					ImGui::InputInt("Strength##exp", &exp->m_pExperience[EXPERIENCE_STRENGTH], 0);
					ImGui::InputInt("Will##exp", &exp->m_pExperience[EXPERIENCE_WILL], 0);
					ImGui::InputInt("Skill##exp", &exp->m_pExperience[EXPERIENCE_SKILL], 0);
				}
			}
		}
		if (morph)
		{
			if (ImGui::CollapsingHeader("Morph"))
			{
				ImGui::SliderFloat("Strength", &morph->m_fStrength, 0.00f, 1.0f);
				ImGui::SliderFloat("Berserk", &morph->m_fBerserk, 0.00f, 1.0f);
				ImGui::SliderFloat("Will", &morph->m_fWill, 0.00f, 1.0f);
				ImGui::SliderFloat("Skill", &morph->m_fSkill, 0.00f, 1.0f);
				ImGui::SliderFloat("Age##morph", &morph->m_fAge, 0.00f, 1.0f);
				ImGui::SliderFloat("Alignment", &morph->m_fAlign, 0.00f, 1.0f);
				ImGui::SliderFloat("Fatness", &morph->m_fFat, 0.00f, 1.0f);

				ImGui::Checkbox("Kid", &morph->m_bKid);
				if (ImGui::Button("Update", ImVec2(-FLT_MIN, 0)))
					morph->m_bUpdate = true;
			}
		}
		ImGui::Text("Position");
		ImGui::InputFloat3("", &t->GetPosition()->X);
}
}

void FableMenu::DrawCameraTab()
{
	if (TheCamera)
	{
		ImGui::Checkbox("Set Camera Position", &m_bCustomCameraPos);
		ImGui::InputFloat3("X | Y | Z", &camPos.X);

		ImGui::Checkbox("Set FOV", &m_bCustomCameraFOV);

		if (m_bCustomCameraFOV)
			ImGui::InputFloat("FOV", &TheCamera->FOV);
		ImGui::Separator();
	}

	ImGui::Checkbox("Free Camera", &ms_bFreeCam);
	if (ms_bFreeCam)
	{
		ImGui::Separator();
		if (!m_bCustomCameraPos)
			ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Check \"Set Camera Position\"!");

		ImGui::Text("Free Camera Type");
		ImGui::Separator();
		ImGui::RadioButton("Custom (Recommended)", &m_nFreeCameraMode, FREE_CAMERA_CUSTOM);
		ImGui::SameLine();
		ShowHelpMarker("A custom free camera implementation, uses NUMPAD keys by default to move the camera. Mouse and key settings can be changed in the Settings menu.");
		ImGui::RadioButton("Original", &m_nFreeCameraMode, FREE_CAMERA_ORIGINAL);
		if (m_nFreeCameraMode == FREE_CAMERA_CUSTOM)
		{
			ImGui::Separator();
			ImGui::InputFloat("Free Camera Speed", &m_fFreeCamSpeed);
		}

		ImGui::Separator();
	}

	if (ImGui::Button("Teleport Player To Camera Location", {-FLT_MIN, 0 }))
	{
		CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetPlayer();
		if (plr)
		{
			CThing* t = plr->GetCharacterThing();
			*t->GetPosition() = TheCamera->pos;
		}
	}

}

void FableMenu::DrawWorldTab()
{
	CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetPlayer();
	CWorld* wrld = CMainGameComponent::Get()->GetWorld();
	if (wrld)
	{
		ImGui::Text("Settings");
		ImGui::Separator();
		ImGui::Checkbox("Minimap", &wrld->m_bMinimap);
		if (plr)
		{
			bool& enemies = *(bool*)((int)plr + 0x21B);
			ImGui::Checkbox("Kill Mode", &enemies);
		}
		ImGui::Separator();
	}
	if (wrld)
	{
		ImGui::Text("Time");
		ImGui::Separator();
		{
			int time = *(int*)((int)wrld + 28);
			if (time)
			{
				float& timeStep = *(float*)((int)time + 16);
				ImGui::SliderFloat("Time Step", &timeStep, 0.001f, 1.0f);

				ImGui::Checkbox("Set Time", &ms_bChangeTime);
				if (ms_bChangeTime)
				{
					float& curTime = *(float*)((int)time + 8);
					ImGui::SliderFloat("Time", &curTime, 0.0, 1.0f);
				}

			}
		}
		ImGui::Separator();
	}

	if (ImGui::CollapsingHeader("Objects"))
	{
		static CVector pos = {};
		static int id = 0;
		static char text[512] = { };
		ImGui::TextWrapped("Spawn Position (X | Y | Z)");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputFloat3("", &pos.X);
		ImGui::PopItemWidth();
		if (ImGui::Button("Get Player Position", { -FLT_MIN, 0 }))
		{
			if (plr)
				pos = *plr->GetCharacterThing()->GetPosition();
		}

		ImGui::Text("Object Name");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("##object", text, sizeof(text));
		ImGui::PopItemWidth();

		if (ImGui::Button("Get ID",{ -FLT_MIN, 0 }))
			id = GetThingID(text);

		ImGui::InputInt("Object ID", &id);

		if (id <= 0)
			ImGui::TextWrapped("Invalid object ID!");
		else
			if (ImGui::Button("Create Object"))
				CreateThing(id, &pos, 0, 0, 0, "newObj");
	}
	if (ImGui::CollapsingHeader("Creatures"))
	{
		static CVector cpos = {};
		static int cid = 0;
		static int caiID = 0;
		static char ctext[512] = { };
		static bool advanced = false;
		static bool playerFollower = false;
		ImGui::TextWrapped("Spawn Position (X | Y | Z)");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputFloat3("", &cpos.X);
		ImGui::PopItemWidth();
		if (ImGui::Button("Get Player Position##creatures", { -FLT_MIN, 0 }))
		{
			if (plr)
				cpos = *plr->GetCharacterThing()->GetPosition();
		}

		ImGui::Text("Creature Name");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputText("##creatures", ctext, sizeof(ctext));
		ImGui::PopItemWidth();

		if (ImGui::Button("Get ID##creatures",{ -FLT_MIN, 0 }))
			cid = GetThingID(ctext);

		ImGui::InputInt("Object ID##creatures", &cid);
		ImGui::Checkbox("Advanced Settings", &advanced);
		if (advanced)
		{
			ImGui::Separator();
			ImGui::InputInt("Owner ID##creatures", &caiID);

			ImGui::TextWrapped("Faction");
			ImGui::PushItemWidth(-FLT_MIN);
			if (ImGui::BeginCombo("##faclist", szFactionName))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szFactions); n++)
				{
					bool is_selected = (szFactionName == szFactions[n]);
					if (ImGui::Selectable(szFactions[n], is_selected))
						sprintf(szFactionName, szFactions[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::PopItemWidth();
			ImGui::Checkbox("Create as player follower", &playerFollower);
			ImGui::SameLine();
			ShowHelpMarker("Creature will follow and defend player, this only works with some creatures (usually those that are simple enough, eg. swords or spirits)");

			ImGui::Separator();
		}
		if (cid <= 0)
			ImGui::TextWrapped("Invalid creature ID!");
		else
			if (ImGui::Button("Create Creature##creatures", { -FLT_MIN, 0 }))
			{
				CThing* creature = CreateCreature(cid, &cpos, caiID);
				if (creature && advanced)
				{
					if (plr)
					{
						CTCEnemy* enemy = creature->GetEnemy();
						CCharString faction(szFactionName);
						enemy->SetFaction(&faction);

						if (playerFollower)
						{
							CTCRegionFollower* rf = plr->GetCharacterThing()->GetRegionFollower();
							enemy->AddAlly(plr->GetCharacterThing());
							CIntelligentPointer ptr(creature);

							rf->AddFollower(*ptr);
						}
						else
						{
							if (strcmp(szFactionName, "FACTION_HERO") == 0)
								enemy->AddAlly(plr->GetCharacterThing());
						}

					}

				}
			}
	}
}

void FableMenu::DrawMiscTab()
{
	ImGui::Checkbox("Display HUD", &GetHud()->m_bDisplay);


	CWorld* wrld = CMainGameComponent::Get()->GetWorld();
	if (wrld)
	{
		CBulletTimeManager* time = wrld->GetBulletTime();
		if (time)
		{
			ImGui::Checkbox("Slowmotion", &time->m_bActive);

		}
	}

	ImGui::Separator();
	ImGui::Text("Cheats");
	ImGui::Separator();
	ImGui::Checkbox("Infinite Health", &m_bGodMode);
	ImGui::Checkbox("Infinite Will", &m_bInfiniteWill);
	ImGui::Separator();
#ifdef _DEBUG
	if (TheCamera)
	{
		ImGui::Text("Camera: 0x%X", TheCamera);
	}
	if (wrld)
	{
		ImGui::Text("World Pointer: 0x%X", wrld);
		ImGui::Text("Game Component Pointer: 0x%X", CMainGameComponent::Get());
		ImGui::Text("Weather Settings: 0x%X", WeatherSettings);
	}

	CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetPlayer();
	if (plr)
	{
		CThing* t = plr->GetCharacterThing();
		ImGui::Text("Player Stats: 0x%X", t->GetHeroStats());
		ImGui::Text("Player Morph: 0x%X\n", t->GetHeroMorph());
		ImGui::Text("Player Experience: 0x%X\n", t->GetHeroExperience());
		ImGui::Text("Player Thing: 0x%X\n", t);
		ImGui::Text("Player: 0x%X\n", plr);
	}
#endif
}

void FableMenu::DrawSettings()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.5f, 0.5f });
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 700,700 }, ImGuiCond_Once);
	ImGui::Begin("Settings", &m_bSubmenuActive[SUBMENU_SETTINGS]);

	static int settingID = 0;
	static const char* settingNames[] = {
		"Menu",
		"INI",
		"Keys",
		"Mouse"
	};

	enum eSettings {
		MENU,
		INI,
		KEYS,
		MOUSE
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(settingNames); n++)
	{
		bool is_selected = (settingID == n);
		if (ImGui::Selectable(settingNames[n], is_selected))
			settingID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (settingID)
	{
	case MENU:
		ImGui::TextWrapped("All user settings are saved to fablemenu_user.ini.");
		ImGui::Text("Menu Scale");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputFloat("", &SettingsMgr->fMenuScale);
		ImGui::PopItemWidth();
		break;
	case INI:
		ImGui::TextWrapped("These settings control FableMenu.ini options. Any changes require game restart to take effect.");
		ImGui::LabelText("", "Core");
		ImGui::Separator();
		ImGui::Checkbox("Slowmotion Spell/Effect Affects Everything", &SettingsMgr->bSlowMotionEffectsEverything);
		ImGui::Checkbox("Windowed Mode", &SettingsMgr->bUseBuiltInWindowedMode);
		ImGui::Separator();

		break;
	case KEYS:
		if (m_bPressingKey)
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");

		if (ImGui::Button("Reset Keys", { -FLT_MIN, 0 }))
		{
			SettingsMgr->ResetKeys();
		}

		ImGui::Separator();
		ImGui::LabelText("", "Core");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iMenuOpenKey, "Open/Close Menu", "menu");
		ImGui::Separator();
		ImGui::LabelText("", "Camera");
		ImGui::Separator();

		KeyBind(&SettingsMgr->iFreeCameraKeyForward, "Forward", "x_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyBack, "Back", "x_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyLeft, "Left", "y_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRight, "Right", "y_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyUp, "Up", "z_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyDown, "Down", "z_minus");
		ImGui::Separator();

		if (m_bPressingKey)
		{
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				*m_pCurrentVarToChange = result;
				m_bPressingKey = false;
			}

		}
		break;
	case MOUSE:
		ImGui::TextWrapped("All user settings are saved to fablemenu_user.ini.");
		ImGui::Text("Sensitivity");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::SliderFloat("", &SettingsMgr->mouse.sens, 0, 10.0f);
		ImGui::PopItemWidth();
		ImGui::Checkbox("Invert X", &SettingsMgr->mouse.invert_x);
		ImGui::Checkbox("Invert Y", &SettingsMgr->mouse.invert_y);
		break;
	default:
		break;
	}

	if (ImGui::Button("Save", { -FLT_MIN, 0 }))
	{
		eDirectX9Hook::ms_bShouldReloadFonts = true;
		MessageBeep(MB_ICONINFORMATION);
		SettingsMgr->SaveSettings();
	}

	ImGui::EndChild();
	ImGui::PopStyleVar();

	ImGui::End();
}

void FableMenu::DrawKeyBind(char* name, int* var)
{
	ImGui::SameLine();

	static char butName[256] = {};
	sprintf(butName, "%s##key%s", eKeyboardMan::KeyToString(*var), name);
	if (ImGui::Button(butName))
	{
		m_bPressingKey = true;
		m_pCurrentVarToChange = var;
	}
}

void FableMenu::KeyBind(int* var, char* bindName, char* name)
{
	ImGui::LabelText("", bindName);
	DrawKeyBind(name, var);
}

void HookWorldUpdate()
{
	if (!InGame())
		return;

	CWorld* wrld = CMainGameComponent::Get()->GetWorld();
	if (wrld)
	{
		CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetPlayer();
		if (plr)
		{
			if (TheMenu->m_bIsActive && !TheMenu->m_bFrozeControls)
			{
				plr->SetMode(17, false);
				TheMenu->m_bFrozeControls = true;
			}
			else if (!TheMenu->m_bIsActive && TheMenu->m_bFrozeControls)
			{
				plr->ClearMode(17);
				TheMenu->m_bFrozeControls = false;
			}

			if (TheMenu->m_bGodMode)
			{
				CThing* t = plr->GetCharacterThing();
				if (t)
					t->m_fHealth = 1000.0f;
			}

			if (TheMenu->m_bInfiniteWill)
			{
				CThing* t = plr->GetCharacterThing();
				if (t)
				{
					CTCHeroStats* stats = t->GetHeroStats();
					stats->m_nWillPower = 10000.0f;
				}
				
			}
			if (TheMenu->m_bCustomCameraPos && TheMenu->ms_bFreeCam && TheMenu->m_nFreeCameraMode == FREE_CAMERA_CUSTOM)
				FreeCamera::Update();
		}

	}
}

bool InGame()
{
	if (CMainGameComponent::Get())
	{
		if (CMainGameComponent::Get()->GetWorld())
			return true;
	}
	return false;
}

float GetDeltaTime()
{
	float delta = 1.0f / 60.0f;

	if (eDirectX9Hook::ms_bInit)
		delta = 1.0f / ImGui::GetIO().Framerate;

	return delta;
}
