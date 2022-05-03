#include "imgui/imgui.h"
#include "IniReader.h"
#include <iostream>
#include <Windows.h>
#include "FableMenu.h"
#include "Fable.h"
#include "eDirectX9Hook.h"
#include "utils/MemoryMgr.h"

using namespace Memory::VP;

FableMenu* TheMenu = new FableMenu();

bool FableMenu::ms_bEnableFreeCamera = false;
bool FableMenu::ms_bFreezeCamera = false;
bool FableMenu::ms_bDisableHUD = false;
bool FableMenu::ms_bChangeFOV = false;
bool FableMenu::ms_bChangeTime = false;
float FableMenu::m_fTime;
void FableMenu::Init()
{
	CIniReader ini("");
}

void FableMenu::Render()
{
	if (!active)
		return;


	ImGui::Begin("FableMenu by ermaccer");
	{
		if (CMainGameComponent::Get())
		{
			if (ImGui::BeginTabBar("##tabs"))
			{
				if (ImGui::BeginTabItem("Player"))
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
							ImGui::Text("Data");
							ImGui::Separator();
							ImGui::InputFloat("Health", &t->m_fHealth);
							ImGui::InputFloat("Max. Health", &t->m_fMaxHealth);
							ImGui::InputInt("Will Power", &stats->m_nWillPower,0);
							ImGui::InputInt("Max. Will", &stats->m_nMaxWillPower,0);
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
							ImGui::Separator();
						}
						if (morph)
						{
							ImGui::Text("Morph");
							ImGui::Separator();
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
							ImGui::Separator();
						}
						ImGui::Text("Position");
						ImGui::InputFloat3("", &t->GetPosition()->x);
					}
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Camera"))
				{
					if (mouseLookCam)
					{
						ImGui::Text("Position");
						ImGui::InputFloat3("X | Y | Z", &mouseLookCam->pos.x);

						ImGui::Checkbox("Change FOV", &ms_bChangeFOV);

						if (ms_bChangeFOV)
							ImGui::InputFloat("FOV", &mouseLookCam->FOV);
						ImGui::Separator();
					}

					ImGui::Checkbox("Freeze Position", &ms_bFreezeCamera);
					ImGui::Checkbox("Free Camera", &ms_bEnableFreeCamera);

					if (ImGui::Button("Teleport Player To Camera Location"))
					{
						CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetPlayer();
						if (plr)
						{
							CThing* t = plr->GetCharacterThing();
							*t->GetPosition() = mouseLookCam->pos;
						}
					}

					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("World"))
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
								ImGui::SliderFloat("Time Step", &timeStep, 0.0, 1.0f);
						
								ImGui::Checkbox("Set Time", &ms_bChangeTime);
								if (ms_bChangeTime)
								{
									float& curTime = *(float*)((int)time + 8);
									ImGui::SliderFloat("Time", &curTime, 0.0, 1.0f);
								}
									
							}
						}
					}

					ImGui::Text("Objects");
					ImGui::Separator();
					{
						static CVector pos = {};
						static int id = 0;
						static char text[512] = { };
						ImGui::InputFloat3("Spawn Position", &pos.x);
						if (ImGui::Button("Get Player Pos."))
						{
							if (plr)
								pos = *plr->GetCharacterThing()->GetPosition();
						}

						ImGui::InputText("Object Name", text, sizeof(text));

						if (ImGui::Button("Get ID"))
							id = GetThingID(text);

						ImGui::InputInt("Object ID", &id);

						if (id <= 0)
							ImGui::TextWrapped("Invalid object ID!");
						else
						if (ImGui::Button("Create Object"))
							CreateThing(id, &pos, 0, 0, 0, "newObj");
					}

					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Misc."))
				{
					ImGui::Checkbox("Display HUD", &GetHud()->m_bDisplay);
					ImGui::Checkbox("God Mode", &godMode);

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
#ifdef _DEBUG
					if (mouseLookCam)
					{
						ImGui::Text("Camera: 0x%X", mouseLookCam);
					}
					if (wrld)
					{
						ImGui::Text("World Pointer: 0x%X", wrld);
						ImGui::Text("Game Component Pointer: 0x%X", CMainGameComponent::Get());
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
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
	}
	ImGui::End();
}

void FableMenu::Process()
{
	if (ms_bChangeFOV)
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
			if (TheMenu->active && !TheMenu->frozeControls)
			{
				plr->SetMode(17, false);
				TheMenu->frozeControls = true;
			}
			else if (!TheMenu->active && TheMenu->frozeControls)
			{
				plr->ClearMode(17);
				TheMenu->frozeControls = false;
			}

			if (TheMenu->godMode)
			{
				CThing* t = plr->GetCharacterThing();
				if (t)
					t->m_fHealth = 1000.0f;
			}
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
