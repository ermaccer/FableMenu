#include "Menu.h"
#include "Settings.h"

#include "../helper/eKeyboardMan.h"
#include "../helper/eMouse.h"

#include "../Fable.h"
#include "../utils/MemoryMgr.h"

#include "../gui/notifications.h"
#include "../gui/imgui/imgui.h"
#include "../gui/gui_impl_dx9.h"

#include "FreeCamera.h"

#include <iostream>
#include <Windows.h>


using namespace Memory::VP;
FableMenu* TheMenu = new FableMenu();

bool FableMenu::ms_bFreeCam = false;
bool FableMenu::m_bCustomCameraPos = false;
bool FableMenu::ms_bDisableHUD = false;
bool FableMenu::m_bCustomCameraFOV = false;
bool FableMenu::ms_bChangeTime = false;
bool FableMenu::ms_bDisableCreateParticle = false;
float FableMenu::m_fTime = 0.0f;
std::vector<CThing*> FableMenu::m_vCreatedParticles;
std::vector<CThing*> FableMenu::m_vAttachedParticles;
bool FableMenu::ms_bSlowmotion = false;

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

static void ShowWarnMarker(const char* desc)
{
    ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "(!)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

FableMenu::FableMenu()
{
    sprintf(szFactionName, szFactions[0]);
}

void FableMenu::OnActivate()
{
    m_bIsActive ^= 1;
}

void FableMenu::Draw()
{
    if (!m_bIsActive)
        return;

    ImGui::GetIO().MouseDrawCursor = true;

    ImGui::Begin("FableMenu by ermaccer, beqwit & unveler", &m_bIsActive, ImGuiWindowFlags_MenuBar);
    {
        ImGui::SetWindowSize({ 550, 450 }, ImGuiCond_Once);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Settings"))
            {
                m_bSubmenuActive[SM_Settings] = true;
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("Creature List"))
                {
                    m_bSubmenuActive[SM_Creature_List] = true;
                }
                if (ImGui::MenuItem("Particle List"))
                {
                    m_bSubmenuActive[SM_Particle_List] = true;
                }
                if (ImGui::MenuItem("Object List"))
                {
                    m_bSubmenuActive[SM_Object_List] = true;
                }
                if (ImGui::BeginMenu("About"))
                {
                    ImGui::MenuItem("Version: " FABLEMENU_VERSION);
                    ImGui::MenuItem("Date: " __DATE__);
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        if (CMainGameComponent::Get())
        {
            if (ImGui::BeginTabBar("##tabs"))
            {
                if (ImGui::BeginTabItem("Hero"))
                {
                    DrawHeroTab();
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Player"))
                {
                    DrawPlayerTab();
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Creatures"))
                {
                    DrawCreaturesTab();
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Objects"))
                {
                    DrawObjectsTab();
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
                if (ImGui::BeginTabItem("Quest"))
                {
                    DrawQuestTab();
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

    if (m_bSubmenuActive[SM_Settings])
        DrawSettings();

    if (m_bSubmenuActive[SM_Particle_List])
        DrawParticleList();

    if (m_bSubmenuActive[SM_Creature_List])
        DrawCreatureList();

    if (m_bSubmenuActive[SM_Object_List])
        DrawObjectList();
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

    if (m_bNoBodyGuardsLimit)
        Patch<char>(0xE60689 + 2, 0xFF);
    else
        Patch<char>(0xE60689 + 2, 2);
    
    if (m_bForceLoadRegion)
    {
        *(int*)NProgressDisplay::PProgressDisplay = 0;
    }
    else if (!*(int*)NProgressDisplay::PProgressDisplay)
    {
        CAProgressDisplay* progressDisplay = (CAProgressDisplay*)GameMalloc(179);
        NProgressDisplay::InitialiseProgressDisplay(progressDisplay);
    }

    // Disable fadeout
    Patch(0x4A411E, { (unsigned char)(m_bForceLoadRegion ? 0x74 : 0x75) });
    // RegionLoadScreenWasFadedOut
    Patch(0x4A415D, { (BYTE)m_bForceLoadRegion });
}

void FableMenu::DrawHeroTab()
{
    CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer();
    if (plr)
    {
        CThing* t = plr->GetCharacterThing();
        CTCHeroStats* stats = (CTCHeroStats*)t->GetTC(TCI_HERO_STATS);
        CTCHeroMorph* morph = (CTCHeroMorph*)t->GetTC(TCI_APPEARANCE_MORPH);
        CTCHeroExperience* exp = (CTCHeroExperience*)t->GetTC(TCI_HERO_EXPERIENCE);
        CTCLook* look = (CTCLook*)t->GetTC(TCI_LOOK);
        CTCHero* hero = (CTCHero*)t->GetTC(TCI_HERO);
        CTCHaste* haste = (CTCHaste*)t->GetTC(TCI_HASTE);
        CTCPhysicsStandard* physics = (CTCPhysicsStandard*)t->GetTC(TCI_PHYSICS);
        CTCCarrying* carrying = (CTCCarrying*)t->GetTC(TCI_CARRYING);
        if (stats)
        {
            if (ImGui::CollapsingHeader("Data"))
            {
                ImGui::InputFloat("Health", &t->m_fHealth);
                ImGui::InputFloat("Max. Health", &t->m_fMaxHealth);
                ImGui::InputInt("Will##data", &stats->m_nStamina, 0);
                ImGui::InputInt("Max. Will", &stats->m_nMaxStamina, 0);
                ImGui::InputInt("Gold", &stats->m_nMoney);
                ImGui::InputFloat("Age", &stats->m_fAge);
                if (hero)
                {
                    ImGui::Checkbox("Can Use Weapons", &hero->m_bCanUseWeapons);
                    ImGui::Checkbox("Can Use Will", &hero->m_bCanUseWill);

                    ImGui::Separator();
                    ImGui::Text("Renown Data");
                    ImGui::Separator();

                    ImGui::InputInt("Renown", &stats->m_nRenownTotal);

                    if (ImGui::SliderInt("Renown Level", &stats->m_nRenownLevel, 1, stats->m_nRenownMaxLevel))
                    {
                        stats->CheckForNewExpressions();
                    }

                    ImGui::InputInt("Renown Points In Level", &stats->m_nRenownPointsInLevel);
                    ImGui::InputInt("Morality", &stats->m_nMorality);

                    static int titleObjectID = 1220;
                    const char* defPrefix = "OBJECT_HERO_TITLE";

                    ImGui::Separator();
                    ImGui::Text("Title");
                    ImGui::Separator();
                    ImGui::PushItemWidth(-FLT_MIN);
                    if (ImGui::BeginCombo("##title", szObjectsList[titleObjectID]))
                    {
                        for (int n = 0; n < IM_ARRAYSIZE(szObjectsList); n++)
                        {
                            if (strncmp(szObjectsList[n], defPrefix, strlen(defPrefix)) != 0)
                            {
                                continue;
                            }

                            bool is_selected = (titleObjectID == n);
                            if (ImGui::Selectable(szObjectsList[n], is_selected))
                                titleObjectID = n;
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                        }

                        ImGui::EndCombo();
                    }
                    ImGui::PopItemWidth();

                    if (ImGui::Button("Set Title", { -FLT_MIN, 0 }))
                    {
                        CGameDefinitionManager* defManager = CGameDefinitionManager::GetDefinitionManager();
                        CCharString titleDef((char*)(szObjectsList[titleObjectID]));

                        int titleDefIndex = defManager->GetDefGlobalIndexFromName(&titleDef);
                        hero->SetTitle(titleDefIndex);
                    }
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

                    if (ImGui::Button("Learn All Abilities"))
                    {
                        for (int i = 1; i < MAX_NUMBER_OF_HERO_ABILITIES; i++)
                        {
                            t->LearnAbility((EHeroAbility)i, 1, -1, 1);
                        }
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Abilities To Max Level"))
                    {
                        CTCInventoryAbilities* abilities = (CTCInventoryAbilities*)t->GetTC(TCI_HERO_ABILITIES);

                        if (abilities)
                            abilities->ForceAllAbilitesToMaxLevel();
                    }
                    if (ImGui::Button("Learn All Expressions", { -FLT_MIN, 0 }))
                    {
                        for (auto expression : expressionNames)
                        {
                            CCharString expressionName((char*)expression);
                            t->LearnExpression(&expressionName, -1, 1);
                        }
                    }
                }
                if (stats)
                {
                    ImGui::Separator();
                    ImGui::Text("Misc.");
                    ImGui::Separator();

                    ImGui::InputFloat("Sound Radius Multiplier", &stats->m_fSoundRadiusMultiplier);
                    ImGui::InputFloat("Visibility Multiplier", &stats->m_fVisibilityMultiplier);
                    ImGui::InputFloat("Max Chicken Throw", &stats->m_fMaxChickenThrow);
                    ImGui::Checkbox("Had Scripted Sex", &stats->m_bHadScriptedSex);
                    ImGui::Checkbox("Had Scripted Gay Sex", &stats->m_bHadScriptedGaySex);
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
                if (ImGui::Button("Update##Morph", ImVec2(-FLT_MIN, 0)))
                    morph->m_bUpdate = true;
            }
        }
        if (carrying)
        {
            if (ImGui::CollapsingHeader("Weapon"))
            {
                CThing* thingPrimarySlot = carrying->GetThingInPrimarySlot();

                if (thingPrimarySlot && thingPrimarySlot->HasTC(TCI_WEAPON))
                {
                    ImGui::Separator();
                    ImGui::Text("Augmentations");
                    ImGui::Separator();

                    CTCObjectAugmentations* augObject = (CTCObjectAugmentations*)thingPrimarySlot->GetTC(TCI_OBJECT_AUGMENTATIONS);
                    int numberOfSlots = augObject->GetNumberOfSlots();
                    static int selectedAug = 0;
                    const char* augmentationDefs[] = {
                        "OBJECT_SHARPENING_AUGMENTATION",
                        "OBJECT_PIERCING_AUGMENTATION",
                        "OBJECT_SILVER_AUGMENTATION",
                        "OBJECT_FLAME_AUGMENTATION",
                        "OBJECT_LIGHTNING_AUGMENTATION",
                        "OBJECT_EXPERIENCE_AUGMENTATION",
                        "OBJECT_HEALTH_AUGMENTATION",
                        "OBJECT_MANA_AUGMENTATION"
                    };
                    static bool slotsLimit = false;

                    ImGui::Text("Damage Multiplier: %f", augObject->GetDamageMultiplier());
                    ImGui::Text("Expirience Multiplier: %f", augObject->GetExperienceMultiplier());

                    ImGui::BeginChild("Augmention Slots", { 0, -ImGui::GetFrameHeightWithSpacing() + 200 }, true);
                    if (numberOfSlots == 0)
                    {
                        ImGui::LabelText("", "No Slots Available");
                    }
                    else
                    {
                        for (int i = 0; i < numberOfSlots; i++)
                        {
                            CWideString name;
                            augObject->GetAugmentationNameInSlot(&name, i);

                            ImGui::LabelText("", "%s", GetUTF8String(name.GetWideStringData()));

                            ImGui::SameLine();
                            ImGui::PushID(i);
                            if (ImGui::Button("Set"))
                            {
                                CCharString augDefName((char*)augmentationDefs[selectedAug]);
                                int augIndex = CGameDefinitionManager::GetDefinitionManager()->GetDefGlobalIndexFromName(&augDefName);
                                augObject->AttachAugmentationToSlot(augIndex, i);
                            }
                            ImGui::SameLine();
                            if (ImGui::Button("Clear"))
                            {
                                augObject->RemoveAugmentationFromSlot(i);
                            }
                            ImGui::PopID();
                        }
                    }
                    ImGui::EndChild();
                    ImGui::LabelText("", "Augmentation Name");
                    ImGui::PushItemWidth(-FLT_MIN);
                    if (ImGui::BeginCombo("##augmentation", augmentationDefs[selectedAug]))
                    {
                        for (int n = 0; n < IM_ARRAYSIZE(augmentationDefs); n++)
                        {
                            bool is_selected = (selectedAug == n);
                            if (ImGui::Selectable(augmentationDefs[n], is_selected))
                                selectedAug = n;
                            if (is_selected)
                                ImGui::SetItemDefaultFocus();
                        }

                        ImGui::EndCombo();
                    }
                    ImGui::PopItemWidth();

                    if (ImGui::Checkbox("Disable Slots Limit", &slotsLimit))
                    {
                        if (slotsLimit)
                        {
                            Nop(0x766D88, 2);
                        }
                        else
                        {
                            Patch(0x766D88, { 0x7D, 0x38 });
                        }
                    }
                    if (ImGui::Button("Add New Slot", { -FLT_MIN, 0 }))
                    {
                        augObject->AddNewSlot();
                    }
                }
                else
                {
                    ImGui::Text("No selected weapon");
                }
            }
        }
        if (haste)
        {
            if (ImGui::CollapsingHeader("Haste"))
            {
                static float combatSpeed = 1;
                ImGui::InputFloat("Adrenaline Multiplier", &combatSpeed);
                if (ImGui::Button("Set Adrenaline", { -FLT_MIN, 0 }))
                {
                    haste->UnsetActionSpeedMultiplier(t);
                    haste->SetActionSpeedMultiplier(t, combatSpeed);
                }
                ImGui::Separator();
                ImGui::Text("Movement");
                ImGui::Separator();

                static const char* movementNames[] = {
                    "Slow Walk",
                    "Walk",
                    "Jog",
                    "Run",
                    "Roll"
                };

                for (int i = 0; i < TOTAL_MOVEMENT_TYPES - 1; i++)
                {
                    float& speed = *(float*)((int)t + 0x18C + (i * sizeof(int)));

                    ImGui::InputFloat(movementNames[i], &speed);
                }

                static int movementType = -1;

                ImGui::Separator();
                ImGui::Text("Movement Type");
                ImGui::Separator();

                ImGui::RadioButton("Default", &movementType, DEFAULT_MOVEMENT);
                ImGui::SameLine();
                ImGui::RadioButton("Walk Movement", &movementType, WALK_MOVEMENT);
                ImGui::SameLine();
                ImGui::RadioButton("Jog Movement", &movementType, JOG_MOVEMENT);
                ImGui::SameLine();
                ImGui::RadioButton("Run Movement", &movementType, RUN_MOVEMENT);

                Memory::VP::Patch(0x6AB514, { 0xB8, (movementType != DEFAULT_MOVEMENT ? (unsigned char)movementType : (unsigned char)JOG_MOVEMENT) });
                Memory::VP::Patch(0x6AB5BC, { 0xB8, (movementType != DEFAULT_MOVEMENT ? (unsigned char)movementType : (unsigned char)RUN_MOVEMENT) });
            }
        }
        if (ImGui::CollapsingHeader("Spell Data"))
        {
            int& curSummonCreature = *(int*)(0x138306C);
            ImGui::TextWrapped("Current Summon Creature ID");
            ImGui::SameLine();
            ShowHelpMarker("You can get desired creature ID from World->Creatures section.");
            ImGui::PushItemWidth(-FLT_MIN);
            ImGui::InputInt("##creaturesumid", &curSummonCreature);
            ImGui::PopItemWidth();
            ImGui::Separator();

        }
        if (ImGui::CollapsingHeader("Input"))
        {
            if (ImGui::Button("Disable Input", { -FLT_MIN, 0 }))
            {
                if (plr)
                    plr->DisableInput();
            }
            if (ImGui::Button("Enable Input", { -FLT_MIN, 0 }))
            {
                if (plr)
                    plr->EnableInput();
            }
        }
        if (ImGui::CollapsingHeader("Appearance"))
        {
            DrawAppearanceCollapse(t);
        }
        if (physics)
        {
            if (ImGui::CollapsingHeader("Physics"))
            {
                DrawPhysicsCollapse(t);
                bool isGravityEnabled = physics->IsGravityEnabled();
                if (ImGui::Checkbox("Enable Gravity", &isGravityEnabled)) 
                { physics->EnableGravity(isGravityEnabled); }
                ImGui::Checkbox("Enable Player Collision", &NGlobalConsole::EnableHeroThingCollision);
            }
        }
    }
}

void FableMenu::DrawPlayerTab()
{
    CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer();

#ifdef _DEBUG
    ImGui::SetWindowFontScale(0.85f);
    ImGui::Text("Player Number: %d", plr->m_dNumber);
    ImGui::SameLine();
    ImGui::Text("Current Mode: %d", plr->GetCurrentMode());
    ImGui::SetWindowFontScale(1.0f);
    ImGui::Separator();
#endif

    if (ImGui::CollapsingHeader("Modes"))
    {
        std::list<enum EPlayerMode> playerModes = plr->m_lPlayerModes;
        int removeID = 0;

        for (EPlayerMode mode : playerModes)
        {
            ImGui::LabelText("", szPlayerModeNames[mode]);
           
            if (playerModes.size() > 1)
            {
                ImGui::SameLine();
                ImGui::PushID(removeID);
                if (ImGui::Button("Remove"))
                {
                    plr->RemoveMode(mode);
                }
                ImGui::PopID();
                removeID++;
            }
        }

        static int modeID = 0;

        if (ImGui::BeginCombo("Mode Name", szPlayerModeNames[modeID]))
        {
            for (int n = 0; n < IM_ARRAYSIZE(szPlayerModeNames); n++)
            {
                bool is_selected = (modeID == n);
                if (ImGui::Selectable(szPlayerModeNames[n], is_selected))
                    modeID = n;
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Add Mode", {-FLT_MIN, 0}))
        {
            plr->AddMode((EPlayerMode)modeID, 0);
        }
        ImGui::Separator();

        static bool aggressiveMode;

        if (ImGui::Checkbox("Aggressive Mode", &aggressiveMode))
        {
            if (!FGlobals::GUsePassiveAggressiveMode)
            {
                FGlobals::GUsePassiveAggressiveMode = 1;
            }

            plr->SetAgressiveMode(aggressiveMode);
        }
    }
    if (ImGui::CollapsingHeader("Actions"))
    {
        DrawActionsCollapse(plr->GetCharacterThing());
    }
    if (ImGui::CollapsingHeader("Character Swap"))
    {
        static bool manualInput = false;
        static bool uninitPlayerCharacter = true;
        static bool playerCharacterDefinitionError = false;
        static int characterID = 0;
        static char selectedPlayerDefManually[256];

        if (playerCharacterDefinitionError)
        {
            ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Invalid character definition");
        }

        static const char* playerCharacterDefs[] =
        {
            "CREATURE_HERO",
            "CREATURE_HERO_BALVERINE",
            "CREATURE_HERO_TRAINING",
            "CREATURE_HERO_CHILD"
        };

        if (!manualInput)
        {
            if (ImGui::BeginCombo("Character Definition", playerCharacterDefs[characterID]))
            {
                for (int n = 0; n < IM_ARRAYSIZE(playerCharacterDefs); n++)
                {
                    bool is_selected = (characterID == n);
                    if (ImGui::Selectable(playerCharacterDefs[n], is_selected))
                        characterID = n;
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }
        else
        {
            ImGui::InputText("Character Definition", selectedPlayerDefManually, sizeof(selectedPlayerDefManually));
        }

        ImGui::Checkbox("Manual Input##mode", &manualInput);
        ImGui::SameLine(); ShowWarnMarker("Defintion has to be compatible with the hero.");
        ImGui::SameLine();
        ImGui::Checkbox("Uninit Character", &uninitPlayerCharacter);
        ImGui::InputFloat3("Repawn Position", &FGlobals::GOverridePlayerStartPos->X);
        if (ImGui::Button("Get Player Position"))
        {
            *FGlobals::GOverridePlayerStartPos = *plr->GetCharacterThing()->GetPosition();
        }
        if (ImGui::Button("Respawn Hero", { -FLT_MIN, 0 }))
        {
            if (!FGlobals::GOverridePlayerStartPosFromConsole)
            {
                FGlobals::GOverridePlayerStartPosFromConsole = 1;
            }

            FGlobals::GUseRubbishMovementMethod = characterID != 1;

            CCharString defName(manualInput ? selectedPlayerDefManually : (char*)playerCharacterDefs[characterID]);

            if (!CGameDefinitionManager::GetDefinitionManager()->GetDefGlobalIndexFromName(&defName))
            {
                playerCharacterDefinitionError = true;
                return;
            }
            else
            {
                playerCharacterDefinitionError = false;
            }

            if (uninitPlayerCharacter)
            {
                plr->UninitCharacter();
            }

            Patch(0x48A0A6, { { (unsigned char)((BYTE)!uninitPlayerCharacter + 0x74) } });

            plr->InitCharacterAs(&defName);
            plr->AddMode(PLAYER_MODE_VIEW_HERO, 0);
            plr->RemoveMode(PLAYER_MODE_VIEW_HERO);
        }
    }
}

void FableMenu::DrawCreaturesTab()
{
    CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer();
    CThing* playerCharacter = plr->GetCharacterThing();
    CThingSearchTools* search = CMainGameComponent::Get()->GetWorld()->GetThingSearchTools();
    std::list<CThing*> regionCreatures = *search->PeekTypeList(1);

    static char creatureName[512] = { };
    static CVector creaturePosition = {};
    static int creatureId;
    static bool advanced;
    static bool playerFollower;

    if (ImGui::CollapsingHeader("Creature Spawner"))
    {
        ImGui::TextWrapped("Spawn Position (X | Y | Z)");
        ImGui::PushItemWidth(-FLT_MIN);
        ImGui::InputFloat3("", &creaturePosition.X);
        ImGui::PopItemWidth();

        if (ImGui::Button("Get Player Position", { -FLT_MIN, 0 }))
        {
            if (plr)
                creaturePosition = *playerCharacter->GetPosition();
        }

        ImGui::Checkbox("Advanced Settings", &advanced);
        if (advanced)
        {
            ImGui::Separator();
            ImGui::InputInt("Owner ID##creatures", &creatureId);

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
            ImGui::Separator();
        }
        ImGui::Text("Creature Name");
        ImGui::SameLine();
        ShowHelpMarker("Creature list is available in Help menu.");
        ImGui::PushItemWidth(-FLT_MIN);
        ImGui::InputText("##creature", creatureName, sizeof(creatureName));
        ImGui::PopItemWidth();

        if (ImGui::Button("Get ID", { -FLT_MIN, 0 }))
        {
            CGameDefinitionManager* defManager = CGameDefinitionManager::GetDefinitionManager();
            CCharString ccsCreatureName((char*)creatureName);
            creatureId = defManager->GetDefGlobalIndexFromName(&ccsCreatureName);
        }

        ImGui::InputInt("Creature ID", &creatureId);

        if (creatureId <= 0)
            ImGui::TextWrapped("Invalid creature ID!");
        else
        {
            if (ImGui::Button("Spawn Creature", { -FLT_MIN, 0 }))
            {
                CThing* creature = CreateCreature(creatureId, &creaturePosition, 0);
                if (creature && advanced)
                {
                    if (plr)
                    {
                        if (!creature->HasTC(TCI_ENEMY))
                        {
                            CCharString enemyTC((char*)"CTCEnemy");
                            creature->AddTC(&enemyTC, 0, 0);
                        }
                        CTCEnemy* enemy = (CTCEnemy*)creature->GetTC(TCI_ENEMY);
                        CCharString faction(szFactionName);
                        enemy->SetFaction(&faction);

                        if (playerFollower)
                        {
                            CIntelligentPointer ptr(creature);
                                
                            CTCRegionFollower* rf = (CTCRegionFollower*)plr->GetCharacterThing()->GetTC(TCI_REGION_FOLLOWER);
                            rf->AddFollower(*ptr);

                            CTCFollowed* pf = (CTCFollowed*)plr->GetCharacterThing()->GetTC(TCI_FOLLOWED);
                            enemy->AddAlly(plr->GetCharacterThing());
                            pf->AddFollower(*ptr, 1);

                            CCharString brainName((char*)"BRAIN_FOLLOW_PLAYER");
                            CGameDefinitionManager* defManager = CGameDefinitionManager::GetDefinitionManager();
                            int brainIndex = defManager->GetDefGlobalIndexFromName(&brainName);
                            int result[1];
                            result[0] = 0;
                            defManager->GetOpinionPersonalitDef(brainIndex, result);
                            creature->SetNewBrain(result[0]);
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
    if (ImGui::CollapsingHeader("Region Creatures"))
    {
        static std::list<CThing*> filteredCreatures;
        static std::vector<char> creatureDataWindowsOpen;
        static bool displayCreatureFilterOptions;
        static int filteredType = 0;

        std::list<CThing*> creatureList;
        filteredCreatures.clear();

        size_t creaturesInLocation = regionCreatures.size();
        ImGui::Text("Creatures In Location: %d", creaturesInLocation);
        ImGui::Separator();

        if (!displayCreatureFilterOptions || filteredType == -1)
        {
            creatureList = regionCreatures;
        }
        else
        {
            for (CThing* t : regionCreatures)
            {
                switch (filteredType)
                {
                case 0:
                    if (t->GetCreatureType() == NOT_HUMAN)
                        filteredCreatures.push_back(t);
                    break;
                case 1:
                    if (t->GetCreatureType() == HUMAN_CHILD)
                        filteredCreatures.push_back(t);
                    break;
                case 2:
                    if (t->GetCreatureType() == HUMAN_ADULT)
                        filteredCreatures.push_back(t);
                    break;
                case 3:
                    if (t->GetCreatureType() == HUMAN_ELDERLY)
                        filteredCreatures.push_back(t);
                    break;
                case 4:
                    if (t->HasTC(TCI_GUARD))
                        filteredCreatures.push_back(t);
                    break;
                case 5:
                    if (t->HasTC(TCI_BANDIT))
                        filteredCreatures.push_back(t);
                    break;
                case 6:
                    if (t->HasTC(TCI_VILLAGE_MEMBER))
                        filteredCreatures.push_back(t);
                    break;
                case 7:
                    if (t->HasTC(TCI_SHOP_KEEPER))
                        filteredCreatures.push_back(t);
                    break;
                case 8:
                    if (t->HasTC(TCI_HERO))
                        filteredCreatures.push_back(t);
                    break;
                default:
                    break;
                }
            }
            creatureList = filteredCreatures;
        }

        ImGui::Checkbox("Creature Filter", &displayCreatureFilterOptions);
        if (displayCreatureFilterOptions)
        {
            ImGui::RadioButton("All", &filteredType, -1);
            ImGui::SameLine();
            ImGui::RadioButton("Not Humans", &filteredType, 0);
            ImGui::SameLine();
            ImGui::RadioButton("Children", &filteredType, 1);
            ImGui::RadioButton("Adults", &filteredType, 2);
            ImGui::SameLine();
            ImGui::RadioButton("Elderly", &filteredType, 3);
            ImGui::SameLine();
            ImGui::RadioButton("Guards", &filteredType, 4);
            ImGui::RadioButton("Bandits", &filteredType, 5);
            ImGui::SameLine();
            ImGui::RadioButton("Traders", &filteredType, 7);
            ImGui::SameLine();
            ImGui::RadioButton("Heroes", &filteredType, 8);
        }

        if (ImGui::Button("Kill All"))
        {
            for (auto creature : creatureList)
            {
                creature->Kill(true);
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Teleport All"))
        {
            for (auto creature : creatureList)
            {
                CTCPhysicsStandard* physics = (CTCPhysicsStandard*)creature->GetTC(TCI_PHYSICS);
                physics->SetPosition(playerCharacter->GetPosition());
            }
        }
        ImGui::Separator();

        size_t creatureCount = creatureList.size();
        creatureDataWindowsOpen.resize(creatureCount, false);

        if (creatureCount != 0)
        {
            int i = 0;

            for (CThing* creature : creatureList)
            {
                CDefString* defName = creature->GetDefName();
                CCharString buffer;
                CDefString::GetString(&buffer, defName->tablePos);
                char* charDefName = buffer.GetStringData();
                const char* thingName = (const char*)charDefName;

                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.15f, 0.75f, 0.35f, 1.0f));
                ImGui::PushItemWidth(420.f);
                ImGui::LabelText("", thingName);
                ImGui::PopStyleColor();
                ImGui::PopItemWidth();
                ImGui::SameLine();
                char* isOpen = &creatureDataWindowsOpen[i];
                ImGui::PushID(i);
                if (ImGui::Button("Open Data"))
                {
                    *isOpen = !(*isOpen);
                }
                ImGui::PopID();

                char windowTitle[256];
                snprintf(windowTitle, sizeof(windowTitle), "%s##%d", thingName, i);

                if (*isOpen)
                {
                    DrawCreatureData(windowTitle, creature, (bool*)isOpen);
                }
                i++;
            }
        }
        else
        {
            ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "No creatures to display");
        }
    }
    if (ImGui::CollapsingHeader("Village"))
    {
        ImGui::Separator();
        ImGui::Text("Village Members");
        ImGui::Separator();

        CTCVillage* village = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer()->GetPNearestTCVillage();

        if (!village)
        {
            ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "No Village");
            return;
        }

        static char villagerDef[256];
        static bool disableVillager = true;
        static bool toggleGuardVillagers = true;
        static bool villageLimbo = true;

        ImGui::InputText("Villager Definition", villagerDef, sizeof(villagerDef));

        if (ImGui::Button((const char*)(disableVillager ? "Disable Villager" : "Enable Villager")))
        {
            CCharString defName(villagerDef);
            village->EnableVillagerDefTypes(villagerDef, &defName);

            disableVillager = !disableVillager;
        }
        ImGui::SameLine(); ShowHelpMarker("Disables creature by definition, works only for village member.");
        if (ImGui::Button("Clear Crimes", { -FLT_MIN, 0 }))
        {
            village->ClearCrimes();
        }
        if (ImGui::Button("Village Limbo", { -FLT_MIN, 0 }))
        {
            village->SetVillageLimbo(villageLimbo);
        }
        ImGui::Separator();
        if (ImGui::Checkbox("Enable Guards", &toggleGuardVillagers))
        {
            village->EnableGuards(toggleGuardVillagers);
        }
        ImGui::Text("Gay Villagers: %d", village->GetNumberOfGayVillagers());
    }
}

void FableMenu::DrawObjectsTab()
{
    static CVector position = {};
    static int objectId = 0;
    static char objectName[512] = { };
    CPlayer* player = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer();

    if (ImGui::CollapsingHeader("Object Spawner"))
    {
        ImGui::TextWrapped("Spawn Position (X | Y | Z)");
        ImGui::PushItemWidth(-FLT_MIN);
        ImGui::InputFloat3("", &position.X);
        ImGui::PopItemWidth();
        if (ImGui::Button("Get Player Position", { -FLT_MIN, 0 }))
        {
            if (player)
                position = *player->GetCharacterThing()->GetPosition();
        }

        ImGui::Text("Object Name");
        ImGui::SameLine();
        ShowHelpMarker("Object list is available in Help menu.");
        ImGui::PushItemWidth(-FLT_MIN);
        ImGui::InputText("##object", objectName, sizeof(objectName));
        ImGui::PopItemWidth();

        if (ImGui::Button("Get ID", { -FLT_MIN, 0 }))
            objectId = GetThingID(objectName);

        ImGui::InputInt("Object ID", &objectId);

        if (objectId <= 0)
            ImGui::TextWrapped("Invalid object ID!");
        else
            if (ImGui::Button("Create Object"))
                CreateThing(objectId, &position, 0, 0, 0, "newObj");
    } 
    if (ImGui::CollapsingHeader("Region Buildings"))
    {
        static std::vector<char> objectDataWindowsOpen;
        CThingSearchTools* searchTools = CMainGameComponent::Get()->GetWorld()->GetThingSearchTools();
        std::list<CThing*> regionBuildings = *searchTools->PeekTypeList(3);
        size_t buildingCount = regionBuildings.size();
        CTCHeroStats* heroStats = (CTCHeroStats*)player->GetCharacterThing()->GetTC(TCI_HERO_STATS);
        int shopsCount = 0;
        objectDataWindowsOpen.resize(buildingCount, false);

        for (auto building : regionBuildings)
        {
            if (building->HasTC(TCI_SHOP))
                shopsCount++;
        }
        ImGui::Text("Shops In Region: %d", shopsCount);
        if (ImGui::Button("Unlock All Doors"))
        {
            std::list<CThing*> allObjects = *searchTools->PeekTypeList(5);
            for (auto object : allObjects)
            {
                CTCDoor* door = (CTCDoor*)object->GetTC(TCI_DOOR);
                if (door)
                {
                    door->Open((CTCAnimationComplex*)1);
                }
            }
        }
        if (ImGui::Button("Evict All Residents"))
        {
            for (auto building : regionBuildings)
            {
                CTCBuyableHouse* buyable = (CTCBuyableHouse*)building->GetTC(TCI_BUYABLE_HOUSE);

                if (buyable)
                {
                    buyable->Evict();
                }
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Own All Buildings"))
        {
            for (auto building : regionBuildings)
            {
                if (building->HasTC(TCI_BUYABLE_HOUSE))
                {
                    CTCBuyableHouse* buyable = (CTCBuyableHouse*)building->GetTC(TCI_BUYABLE_HOUSE);
                    buyable->SetOwnedByPlayer(heroStats);
                }
            }
        }
        ImGui::Separator();
        if (buildingCount != 0)
        {
            int i = 0;
            for (CThing* object : regionBuildings)
            {
                CDefString* defName = object->GetDefName();
                CCharString buffer;
                CDefString::GetString(&buffer, defName->tablePos);
                char* charDefName = buffer.GetStringData();
                const char* thingName = (const char*)charDefName;
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.15f, 0.75f, 0.35f, 1.0f));
                ImGui::LabelText("", thingName);
                ImGui::PopStyleColor();
                ImGui::SameLine();
                char* isOpen = &objectDataWindowsOpen[i];
                ImGui::PushID(i);
                if (ImGui::Button("Open Data"))
                {
                    *isOpen = !(*isOpen);
                }
                ImGui::PopID();

                char windowTitle[256];
                snprintf(windowTitle, sizeof(windowTitle), "%s##%d", thingName, i);

                if (*isOpen)
                {
                    FableMenu::DrawObjectData(windowTitle, object, (bool*)isOpen);
                }
                i++;
            }
        }
    }

    if (ImGui::CollapsingHeader("Region Objects"))
    {
        static std::vector<char> objectDataWindowsOpen;
        CThingSearchTools* searchTools = CMainGameComponent::Get()->GetWorld()->GetThingSearchTools();
        std::list<CThing*> allObjects = *searchTools->PeekTypeList(5);
        size_t objectCount = allObjects.size();
        objectDataWindowsOpen.resize(objectCount, false);
        static ImGuiTextFilter filter;
        static bool canTakeStockItems;
        if (ImGui::Checkbox("Can Take Shop Items", &canTakeStockItems))
        {
            std::list<CThing*> stockItems;
            for (CThing* object : allObjects)
            {
                if (object->HasTC(TCI_STOCK_ITEM))
                    stockItems.push_back(object);
            }
            if (canTakeStockItems)
            {
                for (CThing* stockItem : stockItems)
                {
                    CCharString AddToInventory((char*)"CTCActionUsePutInInventory");
                    stockItem->AddTC(&AddToInventory, 0, 0);
                }
                Patch<char>(0x773538, 0x75);
            }
            else
            {
                for (CThing* stockItem : stockItems)
                {
                    if (stockItem->HasTC(TCI_ON_ACTION_USE))
                        stockItem->RemoveTC(TCI_ON_ACTION_USE);
                }
                Patch<char>(0x773538, 0x74);
            }
        }
        ImGui::Text("Search");
        ImGui::PushItemWidth(-FLT_MIN);
        filter.Draw("##rolist");
        ImGui::PopItemWidth();
        ImGui::BeginChild("##regionObjectsList", { 0, -ImGui::GetFrameHeightWithSpacing() + 200 }, true);
        if (objectCount != 0)
        {
            int i = 0;
            for (CThing* object : allObjects)
            {
                CDefString* defName = object->GetDefName();
                CCharString buffer;
                CDefString::GetString(&buffer, defName->tablePos);
                char* charDefName = buffer.GetStringData();
                const char* thingName = (const char*)charDefName;
                if (filter.PassFilter(thingName))
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.15f, 0.75f, 0.35f, 1.0f));
                    ImGui::LabelText("", thingName);
                    ImGui::PopStyleColor();
                    ImGui::SameLine();
                    char* isOpen = &objectDataWindowsOpen[i];
                    ImGui::PushID(i);
                    if (ImGui::Button("Open Data"))
                    {
                        *isOpen = !(*isOpen);
                    }
                    ImGui::PopID();

                    char windowTitle[256];
                    snprintf(windowTitle, sizeof(windowTitle), "%s##%d", thingName, i);

                    if (*isOpen)
                    {
                        FableMenu::DrawObjectData(windowTitle, object, (bool*)isOpen);
                    }
                    ++i;
                }
            }
        }
        ImGui::EndChild();
    }
}

void FableMenu::DrawAppearanceCollapse(CThing* thing)
{
    static int alpha = 255;
    ImGui::SliderInt("Alpha", &alpha, 0, 255);

    static ImVec4 appearanceColor = { 1.0, 1.0, 1.0, 1.0 };
    ImGui::ColorEdit3("Color", (float*)&appearanceColor);

    static bool highlight = false;
    static ImVec4 highlightColor = { 1.0, 1.0, 1.0, 1.0 };

    ImGui::Checkbox("Change Highlight", &highlight);

    if (highlight)
    {
        ImGui::ColorEdit4("Highlight", (float*)&highlightColor);
    }

    CRGBAFloat acolor(appearanceColor.x, appearanceColor.y, appearanceColor.z, appearanceColor.w);
    CRGBAFloat hcolor(highlightColor.x, highlightColor.y, highlightColor.z, highlightColor.w);

    static float scale = 1.0f;

    CTCGraphicAppearance* ga = (CTCGraphicAppearance*)thing->GetTC(TCI_GRAPHIC_APPEARANCE_NEW);

    ImGui::InputFloat("Scale", &scale);

    if (ImGui::Button("Update##Appearance", { -FLT_MIN, 0 }))
    {
        if (ga)
        {
            ga->SetAlpha(alpha);
            ga->SetColor(&acolor.GetUINTColor(), ga);

            if (highlight)
                ga->SetAsHighlighted(5, 0, &hcolor.GetUINTColor(), 1, 1, MESH_EFFECT_PRIORITY_SHIELD_SPELL_SPECIAL_OVERRIDE, ga);

            ga->SetScale(scale);
        }
    }

    if (ImGui::Button("Clear Highlight", { -FLT_MIN, 0 }))
    {
        ga->ClearHighlighted(ga);
    }

    CTCLight* light = (CTCLight*)thing->GetTC(TCI_LIGHT);

    if (light)
    {
        ImGui::Separator();
        ImGui::Text("Light");
        ImGui::Separator();
        static float lightFlicker = 1.0f;
        static float innerRadius = 1.0f;
        static float outerRadius = 10.0f;
        static ImVec4 lightColor = { 1.0, 1.0, 1.0, 1.0 };

        if (ImGui::InputFloat("Inner Radius", &innerRadius))
        {
            light->SetInnerRadius(innerRadius);
        }
        if(ImGui::InputFloat("Outer Radius", &outerRadius))
        {
            light->SetOuterRadius(outerRadius);
        }
        if (ImGui::ColorEdit3("Light Color", (float*)&lightColor))
        {
            CRGBAFloat lcolor = { lightColor.x, lightColor.y, lightColor.z, lightColor.w };
            light->SetColour(&lcolor.GetUINTColor());
        }
        if (ImGui::Checkbox("Enable Light", &light->m_bActive))
        {
            light->SetOverridden(1);
            light->SetActive(light->m_bActive);
        }
    }
}

void DrawAnimationCollapse(CThing* thing)
{
    static char animInputName[256] = {};
    static bool useInput;
    static int selectedAnimation;
    static bool stayOnLastFrame;
    static bool useMovement;
    static bool addAsQueuedAction;
    static bool waitForAnimToFinish;
    static bool usePhysics;
    static bool allowLooking;
    static bool looping;
    static int numLoops;
    static int animPriority;

    ImGui::Separator();
    ImGui::Text("Animations");
    ImGui::Separator();
    if (!useInput)
    {
        if (ImGui::BeginCombo("##animations", szCreatureAnimations[selectedAnimation]))
        {
            size_t arraySize = sizeof(szCreatureAnimations) / sizeof(szCreatureAnimations[0]);

            for (int i = 0; i < arraySize; i++)
            {
                bool isSelected = (selectedAnimation == i);

                if (ImGui::Selectable(szCreatureAnimations[i], isSelected))
                {
                    selectedAnimation = i;

                    if (isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
            }
            ImGui::EndCombo();
        }
    }
    else
    {
        ImGui::InputText("##anim", animInputName, sizeof(animInputName));
    }
    ImGui::SameLine();
    ImGui::Text("Animation Name");
    ImGui::Checkbox("Manual Input##anim", &useInput);
    ImGui::SameLine();
    ImGui::Checkbox("Looping", &looping);
    ImGui::SameLine();
    ImGui::Checkbox("Use Physics", &usePhysics);
    ImGui::SameLine();
    ImGui::Checkbox("Use Movement", &useMovement);
    ImGui::Checkbox("Allow Looking", &allowLooking);
    ImGui::SameLine();
    ImGui::Checkbox("Stay In Last Frame", &stayOnLastFrame);
    ImGui::SameLine();
    ImGui::Checkbox("Wait For Anim To Finish", &waitForAnimToFinish);
    ImGui::Separator();
    ImGui::InputInt("Animation Priority", &animPriority);
    if (looping)
        ImGui::InputInt("Number Loops", &numLoops);
    if (ImGui::Button("Play Animation", { -FLT_MIN, 0 }))
    {
        CTCScriptedControl* scriptControl = (CTCScriptedControl*)thing->GetTC(TCI_SCRIPTED_CONTROL);
        CTCScriptedControl::CActionBase* animation = (CTCScriptedControl::CActionBase*)GameMalloc(180);

        char* animationName;
        if (!useInput)
            animationName = (char*)szCreatureAnimations[selectedAnimation];
        else
            animationName = animInputName;
        CCharString name(animationName);

        new CActionPlayAnimation(animation, &name, stayOnLastFrame, looping, numLoops, useMovement, animPriority, 0, waitForAnimToFinish, usePhysics, false, allowLooking);
        scriptControl->AddAction(animation);
    }
}

void FableMenu::DrawActionsCollapse(CThing* thing)
{
    DrawAnimationCollapse(thing);

    ImGui::Separator();
    ImGui::Text("Carrying");
    ImGui::Separator();

    static bool destroyDropped = false;
    ImGui::Checkbox("Destroy Dropped Weapon", &destroyDropped);
    if (ImGui::Button("Take Crate"))
    {
        FableMenu::TakeActionItem(thing, (char*)"OBJECT_CRATE_SMALL_EXPLOSIVE_01_USABLE");
    }
    ImGui::SameLine();
    if (ImGui::Button("Drop Carried"))
    {
        // Patch to make it work for swords
        Patch<char>(0x845D86 + 1, 0x84);

        CCreatureAction_DropWeapon* drop = (CCreatureAction_DropWeapon*)GameMalloc(100);
        new CCreatureAction_DropWeapon(drop, thing);

        thing->SetCurrentAction((CTCBase*)drop);

        CTCCarrying* carrying = (CTCCarrying*)thing->GetTC(TCI_CARRYING);

        if (carrying)
        {
            CThing* primarySlotThing = carrying->GetThingInPrimarySlot();

            if (destroyDropped && primarySlotThing)
            {
                if (primarySlotThing->HasTC(TCI_INVENTORY_ITEM))
                {
                    CTCInventoryItem* item = (CTCInventoryItem*)primarySlotThing->GetTC(TCI_INVENTORY_ITEM);
                    item->RemoveFromInventory();
                }
            }
        }
    }
	ImGui::Separator();
    if (ImGui::Button("Finish Current Action"))
    {
        thing->FinishCurrentAction();
    }
}

void FableMenu::DrawPhysicsCollapse(CThing* thing)
{
    ImGui::Separator();
    ImGui::Text("X | Y | Z");
    ImGui::Separator();
    CTCPhysicsStandard* physics = (CTCPhysicsStandard*)thing->GetTC(TCI_PHYSICS);
    ImGui::InputFloat3("Position", &physics->GetPosition()->X);
    if (thing->HasTC(TCI_HERO_STATS))
        ImGui::InputFloat3("Velocity", &physics->GetVelocity()->X);
    ImGui::Separator();
    ImGui::InputFloat3("Forward", &physics->GetRHSet()->Forward.X);
    ImGui::InputFloat3("Up", &physics->GetRHSet()->Up.X);
    ImGui::Separator();

    bool isPhysicsEnabled = physics->IsPhysicsEnabled();

    if (ImGui::Checkbox("Enable Physics", &isPhysicsEnabled))
    {
        physics->EnablePhysics(isPhysicsEnabled);
    }
}

void FableMenu::DrawObjectData(const char* windowTitle, CThing* object, bool* isOpen)
{
    if (!object)
    {
        *isOpen = false;
    }
    if (*isOpen)
    {
        ImGui::SetNextWindowPos({ 700,200 }, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize({ 600,400 }, ImGuiCond_FirstUseEver);
        if (ImGui::Begin(windowTitle, isOpen));
        {
            CTCBuyableHouse* buyableHouse = (CTCBuyableHouse*)object->GetTC(TCI_BUYABLE_HOUSE);

            ImGui::Separator();
            ImGui::Text("Object");
            ImGui::Separator();
            if (ImGui::Button("Show"))
            {
                object->SetInLimbo(0);
            }
            ImGui::SameLine();
            if (ImGui::Button("Hide"))
            {
                object->SetInLimbo(1);
            }
            if (object->HasTC(TCI_STOCK_ITEM) || object->HasTC(TCI_HERO_RECEIVE_ITEMS))
            {
                if (ImGui::Button("Add To Inventory"))
                {
                    CThing* playerCharacter = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer()->GetCharacterThing();
                    CCreatureAction_AddRealObjectToInventory* addToInventory = (CCreatureAction_AddRealObjectToInventory*)GameMalloc(180);
                    new CCreatureAction_AddRealObjectToInventory(addToInventory, playerCharacter, object);
                    playerCharacter->SetCurrentAction((CTCBase*)addToInventory);
                }
            }
            if (!buyableHouse)
            {
                if (ImGui::Button("Teleport To Player Position"))
                {
                    CTCPhysicsStandard* objectPhysics = (CTCPhysicsStandard*)object->GetTC(TCI_PHYSICS);
                    CThing* playerCharacter = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer()->GetCharacterThing();
                    objectPhysics->SetPosition(playerCharacter->GetPosition());
                    objectPhysics->EnablePhysics(0);
                }
            }
            CTCChest* chest = (CTCChest*)object->GetTC(TCI_CONTAINER);
            if (chest)
            {
                ImGui::Separator();
                ImGui::Text("Chest");
                ImGui::Separator();

                if (ImGui::Button("Open", { -FLT_MIN, 0 }))
                {
                    chest->Open();
                }
                if (ImGui::Button("Close", { -FLT_MIN, 0 }))
                {
                    chest->Close();
                }
            }
            if (buyableHouse)
            {
                ImGui::Separator();
                ImGui::Text("House Features");
                ImGui::Separator();
                bool isUsed = buyableHouse->isBuildingBeingUsed(0);
                ImGui::Text("Occupied: %s", isUsed ? "Yes" : "No");

                if (ImGui::Button("Remove Owner"))
                {
                    buyableHouse->Evict();
                }
                ImGui::SameLine();

                if (ImGui::Button("Set Rented"))
                {
                    buyableHouse->SetRented(1);
                }

                if (ImGui::Button("Set Owned By Player"))
                {
                    CThing* playerCharacter = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer()->GetCharacterThing();
                    CTCHeroStats* heroStats = (CTCHeroStats*)playerCharacter->GetTC(TCI_HERO_STATS);
                    if(heroStats)
                        buyableHouse->SetOwnedByPlayer(heroStats);
                }
            }
            ImGui::Separator();
            if (ImGui::CollapsingHeader("Physics"))
            {
                DrawPhysicsCollapse(object);
            }
            if (ImGui::CollapsingHeader("Appearance"))
            {
                DrawAppearanceCollapse(object);
            }
            ImGui::End();
        }
    }
}

void FableMenu::DrawCreatureData(const char* windowTitle, CThing* creature, bool* isOpen)
{
    if (!creature)
    {
        *isOpen = false;
    }
    if (*isOpen)
    {
        ImGui::SetNextWindowPos({ 700,200 }, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize({ 600,500 }, ImGuiCond_FirstUseEver);

        if (ImGui::Begin(windowTitle, isOpen));
        {
            ImGui::Separator();
            ImGui::Text("Data");
            ImGui::Separator();

            if (ImGui::InputFloat("Health", &creature->m_fHealth))
            {
                if (creature->m_fHealth > creature->m_fMaxHealth)
                    creature->m_fMaxHealth = creature->m_fHealth;
            }
            if (ImGui::Button("Kill"))
            {
                creature->Kill(true);
                *isOpen = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Teleport To Player Position"))
            {
                CTCPhysicsStandard* creaturePhysics = (CTCPhysicsStandard*)creature->GetTC(TCI_PHYSICS);
                CThing* playerCharacter = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer()->GetCharacterThing();
                creaturePhysics->SetPosition(playerCharacter->GetPosition());
            }
            if (ImGui::Button("Finish Current Action"))
            {
                creature->FinishCurrentAction();
                creature->ClearQueuedActions();
            }
            ImGui::Separator();
            ImGui::Text("Limbo");
            ImGui::Separator();
            if (ImGui::Button("Show"))
            {
                creature->SetInLimbo(0);
            }
            ImGui::SameLine();
            if (ImGui::Button("Hide"))
            {
                creature->SetInLimbo(1);
            }
            ImGui::Separator();
            if (ImGui::CollapsingHeader("Behavior"))
            {
                ImGui::Separator();
                ImGui::Text("Brain");
                ImGui::Separator();
                static int brainID = 0;

                if (ImGui::BeginCombo("##CreatureBrain", szBrainNames[brainID]))
                {
                    for (int i = 0; i < IM_ARRAYSIZE(szBrainNames); i++)
                    {
                        bool isSelected = (brainID == i);

                        if (ImGui::Selectable(szBrainNames[i], isSelected))
                        {
                            brainID = i;

                            if (isSelected)
                            {
                                ImGui::SetItemDefaultFocus();
                            }
                        }
                    }
                    ImGui::EndCombo();
                }

                ImGui::SameLine();
                ImGui::Text("Brain Name");

                if (ImGui::Button("Set Brain"))
                {
                    ImGui::Text("Brain");
                    ImGui::Separator();
                    CCharString brainName((char*)szBrainNames[brainID]);
                    CGameDefinitionManager* defManager = CGameDefinitionManager::GetDefinitionManager();

                    int brainIndex = defManager->GetDefGlobalIndexFromName(&brainName);

                    int brawlik[1];
                    brawlik[0] = 0;

                    defManager->GetOpinionPersonalitDef(brainIndex, brawlik);

                    creature->SetNewBrain(brawlik[0]);
                }

                ImGui::Separator();
                ImGui::Text("Combat");
                ImGui::Separator();

                static int attackStyleID;

                if (ImGui::BeginCombo("##CreatureAttackStyle", szAttackStyleNames[attackStyleID]))
                {
                    for (int i = 0; i < IM_ARRAYSIZE(szAttackStyleNames); i++)
                    {
                        bool isSelected = (attackStyleID == i);

                        if (ImGui::Selectable(szAttackStyleNames[i], isSelected))
                        {
                            attackStyleID = i;

                            if (isSelected)
                            {
                                ImGui::SetItemDefaultFocus();
                            }
                        }
                    }
                    ImGui::EndCombo();
                }

                ImGui::SameLine();
                ImGui::Text("Combat Name");

                if (ImGui::Button("Set Combat"))
                {
                    CGameDefinitionManager* defManager = CGameDefinitionManager::GetDefinitionManager();
                    CCharString combatName((char*)szAttackStyleNames[attackStyleID]);

                    int combatType = 0;
                    defManager->GetBrainDef(&combatName, &combatType);

                    CTCCombat* combat = (CTCCombat*)creature->GetTC(TCI_COMBAT);
                    combat->SetCombatType(&combatType);
                }
                if (creature->HasTC(TCI_ENEMY))
                {
                    ImGui::Separator();
                    ImGui::Text("Faction");
                    ImGui::Separator();
                    CThing* playerCharacter = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer()->GetCharacterThing();
                    CTCEnemy* enemy = (CTCEnemy*)creature->GetTC(TCI_ENEMY);

                    bool isEnemy = enemy->IsEnemyOf(playerCharacter);
                    ImGui::Text("Is Hero Enemy: %s", isEnemy ? "Yes" : "No");

                    static int factionID = 0;
                    if (ImGui::BeginCombo("##CreatureFaction", szFactions[factionID]))
                    {
                        for (int i = 0; i < IM_ARRAYSIZE(szFactions); i++)
                        {
                            bool isSelected = (factionID == i);

                            if (ImGui::Selectable(szFactions[i], isSelected))
                            {
                                factionID = i;

                                if (isSelected)
                                {
                                    ImGui::SetItemDefaultFocus();
                                }
                            }
                        }
                        ImGui::EndCombo();
                    }
                    ImGui::SameLine();
                    ImGui::Text("Faction Name");
                    if (ImGui::Button("Set Faction"))
                    {
                        CCharString factionName((char*)szFactions[factionID]);
                        enemy->SetFaction(&factionName);
                    }
                }
            }
            if (ImGui::CollapsingHeader("Physics"))
            {
                DrawPhysicsCollapse(creature);
            }
            if (ImGui::CollapsingHeader("Modes"))
            {
                static int creatureModeID;
                CTCCreatureModeManager* modeManager = (CTCCreatureModeManager*)creature->GetTC(TCI_ENTITY_MODE_MANAGER);
                if (ImGui::BeginCombo("Mode Name", szCreatureModeNames[creatureModeID]))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(szCreatureModeNames); n++)
                    {
                        bool is_selected = (creatureModeID == n);
                        if (ImGui::Selectable(szCreatureModeNames[n], is_selected))
                            creatureModeID = n;
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                NCreatureMode::EMode creatureMode = (NCreatureMode::EMode)creatureModeID;

                if (ImGui::Button("Add Mode"))
                {
                    modeManager->AddMode(creatureMode);
                }
                if (ImGui::Button("Remove Mode"))
                {
                    modeManager->RemoveMode(creatureMode);
                }
                ImGui::SameLine();
                if (ImGui::Button("Reset Modes"))
                {
                    for (int n = 0; n < IM_ARRAYSIZE(szCreatureModeNames); n++)
                    {
                        if (modeManager->IsModeActive((NCreatureMode::EMode)n))
                            modeManager->RemoveMode((NCreatureMode::EMode)n);
                    }
                    modeManager->SetupDefaultMode();
                }
            }

            bool hasAnimationTC = creature->HasTC(TCI_ANIMATION);

            if (!hasAnimationTC)
            {
                ImGui::BeginDisabled();
            }
            if (ImGui::CollapsingHeader("Animations"))
            {
                DrawAnimationCollapse(creature);
            }
            if (!hasAnimationTC)
            {
                ImGui::EndDisabled();
            }

            bool hasCarryngTC = creature->HasTC(TCI_CARRYING);

            if (!hasCarryngTC)
            {
                ImGui::BeginDisabled();
            }

            if (ImGui::CollapsingHeader("Carrying"))
            {
                static int selectedCarrySlot;
                static int selectedWeaponID = 0;
                CTCCarrying* carry = (CTCCarrying*)creature->GetTC(TCI_CARRYING);
                bool isCarryWeapon = carry->IsCarryingWeapon(creature);

                ImGui::Text("Is Carrying Weapons: %s", isCarryWeapon ? "Yes" : "No");

                if (ImGui::BeginCombo("##WeaponType", szCreatureWeapons[selectedWeaponID]))
                {
                    for (int i = 0; i < IM_ARRAYSIZE(szCreatureWeapons); i++)
                    {
                        bool isSelected = (selectedWeaponID == i);

                        if (ImGui::Selectable(szCreatureWeapons[i], isSelected))
                        {
                            selectedWeaponID = i;

                            if (isSelected)
                            {
                                ImGui::SetItemDefaultFocus();
                            }
                        }
                    }
                    ImGui::EndCombo();
                }
                ImGui::RadioButton("Right Hand", &selectedCarrySlot, 0);
                ImGui::SameLine();
                ImGui::RadioButton("Left Hand", &selectedCarrySlot, 1);
                ImGui::SameLine();
                ImGui::RadioButton("Both Hands", &selectedCarrySlot, 2);

                static const char* szCarrySlots[] = {
                    "CARRY_SLOT_RIGHT_HAND",
                    "CARRY_SLOT_LEFT_HAND"
                };

                if (ImGui::Button("Add Thing"))
                {
                    CGameDefinitionManager* defManager = CGameDefinitionManager::GetDefinitionManager();
                    CCharString thingName((char*)szCreatureWeapons[selectedWeaponID]);
                    int thingIndex = defManager->GetDefGlobalIndexFromName(&thingName);
                    CThing* thing = CreateThing(thingIndex, creature->GetPosition(), 0, 0, 0, (char*)"obj");

                    if (selectedCarrySlot != 2)
                    {
                        CCharString slotName((char*)szCarrySlots[selectedCarrySlot]);
                        int index = defManager->GetDefGlobalIndexFromName(&slotName);
                        if (!carry->IsCarrySlotFree(index))
                        {
                            CThing* thingInSlot = carry->GetThingInCarrySlot(index);
                            carry->RemoveThingInCarrySlot(index, true);
                            thingInSlot->Kill(0);
                        }
                        carry->AddThingInCarrySlot(thing, index, true);
                    }
                    else 
                    {
                        creature->ClearQueuedActions();
                        creature->FinishCurrentAction();
                        CCreatureAction_PickUpGenericBox* genericBox = (CCreatureAction_PickUpGenericBox*)malloc(180);
                        new CCreatureAction_PickUpGenericBox(genericBox, creature, thing);
                        creature->SetCurrentAction((CTCBase*)genericBox);
                    }
                }

                if (ImGui::Button("Remove Thing"))
                {
                    if (selectedCarrySlot != 2)
                    {
                        CGameDefinitionManager* defManager = CGameDefinitionManager::GetDefinitionManager();
                        CCharString slotName((char*)szCarrySlots[selectedCarrySlot]);
                        int index = defManager->GetDefGlobalIndexFromName(&slotName);
                        CThing* thingInSlot = carry->GetThingInCarrySlot(index);

                        if (!carry->IsCarrySlotFree(index))
                        {
                            carry->RemoveThingInCarrySlot(index, true);
                            thingInSlot->Kill(0);
                        }
                    }
                }
            }

            if (!hasCarryngTC)
            {
                ImGui::EndDisabled();
            }

            if (ImGui::CollapsingHeader("Wife"))
            {
                CTCWife* wife = (CTCWife*)creature->GetTC(TCI_WIFE);

                if (ImGui::Button("Set As Wife", { -FLT_MIN, 0 }))
                {
                    if (!creature->HasTC(TCI_WIFE))
                    {
                        CCharString tcName((char*)"CTCWife");
                        creature->AddTC(&tcName, 0, 0);
                    }
                }

                if (!wife)
                {
                    ImGui::BeginDisabled();
                }

                if (ImGui::Button("Marry", { -FLT_MIN, 0 }))
                {
                    wife->Marry(0);
                }

                bool isSexDisabled = creature->IsChild() && wife;

                if (isSexDisabled)
                {
                    ImGui::BeginDisabled();
                }

                if (ImGui::Button("Have Sex", { -FLT_MIN, 0 }))
                {
                    wife->HaveSex();
                }

                if (isSexDisabled)
                {
                    ImGui::EndDisabled();
                }

                if (ImGui::Button("Divorce", { -FLT_MIN, 0 }))
                {
                    wife->Divorce();
                }

                if (!wife)
                {
                    ImGui::EndDisabled();
                }
            }
            if (ImGui::CollapsingHeader("Appearance"))
            {
                DrawAppearanceCollapse(creature);
            }
            ImGui::End();
        }
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

    if (ImGui::Button("Teleport Player To Camera Location", { -FLT_MIN, 0 }))
    {
        CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer();
        if (plr)
        {
            CThing* t = plr->GetCharacterThing();
            *t->GetPosition() = TheCamera->pos;
        }
    }

}

void FableMenu::DrawWorldTab()
{
    CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer();
    CWorld* wrld = CMainGameComponent::Get()->GetWorld();
    if (wrld)
    {
        ImGui::Separator();
        ImGui::Text("Settings");
        ImGui::Separator();
        bool* minimap = wrld->GetMinimap();
        ImGui::Checkbox("Minimap", minimap);
        if (plr)
        {
            bool& enemies = *(bool*)((int)plr + 0x21B);
            ImGui::Checkbox("Kill Mode", &enemies);
        }
        ImGui::Checkbox("Enemy God Mode", &NGlobalConsole::EnemyGodMode);
        static bool fishingAnywhere;
        if (ImGui::Checkbox("Land Fishing", &fishingAnywhere))
        {
            Patch(0x7F0210, { (unsigned char)((BYTE)fishingAnywhere + 0x74) });
        }
        ImGui::Separator();
    }
    if (wrld)
    {
        if (ImGui::CollapsingHeader("Time"))
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
                    ImGui::SliderFloat("Time##set", &curTime, 0.0, 1.0f);
                }
            }
        }
    }
    if (ImGui::CollapsingHeader("Region"))
    {
        static int hspID = 0;
        static char hspName[256] = {};
        static bool manualInput = false;

        bool& quest_regions = *(bool*)(0x1375741);
        ImGui::Checkbox("Quest Regions", &quest_regions);
        static bool disableRegionBounds;
        if (ImGui::Checkbox("Disable Region Bounds", &disableRegionBounds))
        {
            if (disableRegionBounds)
            {
                Patch(0x81F3F6, { 0xB0, 0x01 });
            }
            else
            {
                Patch(0x81F3F6, { 0x8A, 0x44 });
            }
        }
        ImGui::Separator();
        if (m_bForceLoadRegion)
        {
            ImGui::BeginDisabled();
        }
        ImGui::Text("Hero Spawn Point");
        if(!manualInput)
        {
            if (ImGui::BeginCombo("##hsplist", szHolySites[hspID]))
            {
                for (int n = 0; n < IM_ARRAYSIZE(szHolySites); n++)
                {
                    bool is_selected = (hspID == n);
                    if (ImGui::Selectable(szHolySites[n], is_selected))
                        hspID = n;
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }
        }
        else
        {
            ImGui::InputText("##hspname", hspName, sizeof(hspName));
        }
        ImGui::Checkbox("Manual Input", &manualInput);
        if (ImGui::Button("Teleport", { -FLT_MIN, 0 }))
        {
            if (ms_bSlowmotion)
            {
                wrld->GetBulletTime()->m_bActive = 0;
            }

            CCharString hsp_name(manualInput ? hspName : (char*)szHolySites[hspID]);
            wrld->TeleportHeroToHSP(&hsp_name);
        }
        if (m_bForceLoadRegion)
        {
            ImGui::EndDisabled();
        }
        if (ImGui::Button("Reload Region", { -FLT_MIN, 0 }))
        {
            CWorldMap* map = CThing::GetWorldMap();
            map->ReloadCurrentRegion();
        }
    }
    if (ImGui::CollapsingHeader("Particles"))
    {
        ImGui::TextWrapped("Particle list is available in Help menu.");
        static CVector particlePosition = {};
        static char particleName[512];
        static int attachType;
        static bool isTemporaryParticle;
        static bool attachParticleToCamera;
        static bool particleNameError;

        ImGui::Checkbox("Enable Particles", &NGlobalConsole::EnableParticles);
        ImGui::InputText("Particle Name", particleName, sizeof(particleName));
        ImGui::InputFloat3("Particle Position", &particlePosition.X);
        if (ImGui::Button("Get Player Position"))
        {
            CThing* playerCharacter = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer()->GetCharacterThing();
            particlePosition = *playerCharacter->GetPosition();
        }
        ImGui::RadioButton("Default", &attachType, -1);
        ImGui::SameLine();
        ImGui::RadioButton("Attach To Camera", &attachType, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Attach To Body", &attachType, 1);

        if (ms_bDisableCreateParticle)
            ImGui::BeginDisabled();

        if (ImGui::Button("Create Particle", { -FLT_MIN, 0 }))
        {
            CCharString ccstrParticle(particleName);
            CParticleEmitterDatabase* emitterDatabase = CParticleEmitterDatabase::Get();
            int partId = emitterDatabase->GetEmitterTemplateHandleFromName(&ccstrParticle);

            if (partId <= 0)
            {
                particleNameError = true;
            }
            else
            {
                if (particleNameError)
                {
                    particleNameError = false;
                }

                CThing* particleThing = CTCDParticleEmitter::Create(partId, &particlePosition, false);
                m_vCreatedParticles.push_back(particleThing);

                if (attachType != -1)
                {
                    CTCDParticleEmitter* particleEmitter = (CTCDParticleEmitter*)particleThing->GetTC(TCI_PARTICLE_EMITTER);

                    if(attachType == 0)
                    {
                        particleEmitter->AttachToCamera(8, 0.0);
                    }
                    else if (attachType == 1)
                    {
                        CThing* playerCharacter = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer()->GetCharacterThing();
                        CCharString name("body");
                        particleEmitter->AttachToThing(playerCharacter, 10, &name, 0, 0.0);
                    }

                    m_vAttachedParticles.push_back(particleThing);
                }
            }
        }

        if (particleNameError)
        {
            ImGui::Text("Error: Undefined particle name");
        }

        if (ms_bDisableCreateParticle)
            ImGui::EndDisabled();

        if (ImGui::Button("Clear Attachments", { 125, 25 }))
        {
            for (auto attachedParticle : m_vAttachedParticles)
            {
                if (attachedParticle->isThingAlive())
                {
                    if (attachedParticle->HasTC(TCI_PARTICLE_EMITTER))
                    {
                        CTCDParticleEmitter* attached = (CTCDParticleEmitter*)attachedParticle->GetTC(TCI_PARTICLE_EMITTER);
                        attached->ClearAttachments();
                    }
                }
            }
            m_vAttachedParticles.clear();
        }
        ImGui::SameLine();
        if (ImGui::Button("Destroy All Created Particles", { 200, 25 }))
        {
            for (auto thing : m_vCreatedParticles)
            {
                if (thing->isThingAlive())
                {
                    thing->Kill(false);
                }
            }
            m_vCreatedParticles.clear();
            m_vAttachedParticles.clear();
        }
    }
}

void FableMenu::DrawQuestTab()
{
    if (!CQuestManager::Get())
        return;


    CQuestManager* q = CQuestManager::Get();

    ImGui::TextWrapped("NOTE: Quest changes might break your savegame! To be safe, do any quest changes on a backup/alternative save.");

    static char scriptName[256] = {};
    if (ImGui::CollapsingHeader("Status Control"))
    {
        ImGui::Text("Quest Name");
        static bool writeName = false;

        ImGui::PushItemWidth(-FLT_MIN);

        if (!writeName)
        {
            if (ImGui::BeginCombo("#qststatus", scriptName))
            {
                for (int n = 0; n < IM_ARRAYSIZE(szBuiltInQuests); n++)
                {
                    bool is_selected = (scriptName == szBuiltInQuests[n]);
                    if (ImGui::Selectable(szBuiltInQuests[n], is_selected))
                        sprintf(scriptName, szBuiltInQuests[n]);
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }
        else
        {
            ImGui::InputText("##quest", scriptName, sizeof(scriptName));
        }
        ImGui::Checkbox("Manual Input", &writeName);

        ImGui::PopItemWidth();

        if (strlen(scriptName) > 0)
        {
            if (ImGui::Button("Activate", { -FLT_MIN, 0 }))
            {
                CCharString str(scriptName);
                if (q->IsQuestActive(&str))
                {
                    Notifications->SetNotificationTime(2500);
                    Notifications->PushNotification("Quest \"%s\" is already active!", scriptName);
                }
                else
                {
                    if (q->ActivateQuest(&str, false, true))
                    {
                        Notifications->SetNotificationTime(2500);
                        Notifications->PushNotification("Quest \"%s\" activated!", scriptName);
                    }
                    else
                    {
                        Notifications->SetNotificationTime(2500);
                        Notifications->PushNotification("Failed to activate quest \"%s\"!", scriptName);
                    }
                }

            }
            if (ImGui::Button("Deactivate", { -FLT_MIN, 0 }))
            {
                CCharString str(scriptName);
                if (!q->IsQuestActive(&str))
                {
                    Notifications->SetNotificationTime(2500);
                    Notifications->PushNotification("Quest \"%s\" is not active!", scriptName);
                }
                else
                {
                    q->DeactivateQuest(&str, 0);
                    Notifications->SetNotificationTime(2500);
                    Notifications->PushNotification("Quest \"%s\" deactivated!", scriptName);
                }
            }
        }
    }
    if (ImGui::CollapsingHeader("Active Quests"))
    {
        static bool coreQuest = false;
        static bool optionalQuests = false;
        static bool scriptQuests = false;
        static bool localizedQuests = false;
        int activeQuests = 0;

        ImGui::Checkbox("Core Quests", &coreQuest);
        ImGui::SameLine();
        ImGui::Checkbox("Optional Quests", &optionalQuests);
        ImGui::SameLine();
        ImGui::Checkbox("Scripts", &scriptQuests);
        ImGui::SameLine();
        ImGui::Checkbox("Localize Names", &localizedQuests);
        ImGui::Separator();

        for (int i = 0; i < IM_ARRAYSIZE(szBuiltInQuests); i++)
        {
            CCharString quest_name((char*)szBuiltInQuests[i]);
            const char* localizedName = "NONAME_QUEST";

            if (q->IsQuestActive(&quest_name))
            {
                activeQuests++;

                CThing* cardThing = q->GetActiveQuestCardFromScriptName(&quest_name);
                bool isScript = !cardThing;

                if (isScript && !scriptQuests)
                {
                    continue;
                }

                if (!isScript)
                {
                    CTCQuestCard* card = (CTCQuestCard*)cardThing->GetTC(TCI_QUEST_CARD);

                    if (localizedQuests)
                    {
                        CWideString name;
                        card->GetQuestName(&name);
                        localizedName = GetUTF8String(name.GetWideStringData());
                    }

                    if (coreQuest || optionalQuests)
                    {
                        bool isCore = (coreQuest && card->IsRouteToAppearOnMinimap());
                        bool isOptional = (optionalQuests && card->IsOptional());

                        if (!isCore && !isOptional)
                        {
                            continue;
                        }
                    }
                }

                if (localizedQuests && !isScript)
                {
                    if (strcmp(localizedName, "NONAME_QUEST") == 0)
                    {
                        continue;
                    }

                    ImGui::LabelText("", localizedName);
                }
                else
                {
                    ImGui::LabelText("", szBuiltInQuests[i]);
                }
                ImGui::SameLine();
                ImGui::PushID(i);
                if (ImGui::Button("Deactivate"))
                {
                    q->DeactivateQuest(&quest_name, 0);

                }
                if (cardThing)
                {
                    ImGui::SameLine();
                    if (ImGui::Button("Complete"))
                    {
                        CTCQuestCard* card = (CTCQuestCard*)cardThing->GetTC(TCI_QUEST_CARD);
                        q->SetQuestAsCompleted(&quest_name, 0, 0, 0);
                    }
                }
                ImGui::PopID();
            }
        }
#ifdef _DEBUG
        if (activeQuests > 0)
        {
            if (ImGui::Button("Deactivate All", { -FLT_MIN, 0 }))
            {
                q->DeactivateAllQuests();
                Notifications->SetNotificationTime(2500);
                Notifications->PushNotification("All quests deactivated! (%d)", activeQuests);
                activeQuests = 0;
            }
        }
#endif
    }

    if (ImGui::CollapsingHeader("Tweaks"))
    {
        ImGui::Checkbox("No Bodyguards Limit", &m_bNoBodyGuardsLimit);
        ImGui::SameLine(); ShowHelpMarker("Allows to hire all bodyguards. Default limit is 2.");
        ImGui::Checkbox("Locking Leave Quest Region", &NGlobalConsole::GEnableRegionLockingSaveSystem);
    }
}

void FableMenu::DrawMiscTab()
{
    CWorld* wrld = CMainGameComponent::Get()->GetWorld();
    ImGui::Separator();
    ImGui::Text("Time");
    ImGui::Separator();

    if (wrld)
    {
        CBulletTimeManager* time = wrld->GetBulletTime();
        if (time)
        {
            if (ImGui::Checkbox("Slowmotion", &time->m_bActive))
            {
                ms_bSlowmotion = time->m_bActive;
            }
        }
    }

    ImGui::Checkbox("Update AI", &NGlobalConsole::EnableUpdateAI);
    ImGui::Checkbox("Update Objects", &NGlobalConsole::EnableUpdateObjects);

    static bool creatureDecay = 1;
    static bool enableShortMelee = 0;
    if (ImGui::Checkbox("Dead Creature Decay", &creatureDecay))
    {
        Patch<char>(0x8362EA + 1, creatureDecay + 0x84);
    }
    ImGui::Separator();
    ImGui::Text("Hero");
    ImGui::Separator();

    ImGui::Checkbox("Hero God Mode", &NGlobalConsole::HeroGodMode);
    ImGui::Checkbox("Enable Hero Jump", &NGlobalConsole::EnableHeroJump);
    char jumpDesc[256];
    sprintf(jumpDesc, "Jump action assigned to \"%s\" button. Jump key and others can be changed in settings menu.", eKeyboardMan::KeyToString(SettingsMgr->iHeroJumpKey));
    ImGui::SameLine(); ShowHelpMarker(jumpDesc);
    ImGui::Checkbox("Enable Hero Sprint", &NGlobalConsole::EnableHeroSprint);

    ImGui::Separator();
    ImGui::Text("Display");
    ImGui::Separator();

    ImGui::Checkbox("Display HUD", &GetHud()->m_bDisplay);
    if (ImGui::Checkbox("Hide Auto Save Progress", &FGlobals::GDoNotCallStartAutoSaveProgress))
    {
        // Patch SaveGameState variable reset
        Patch(0x4A073B, { (BYTE)FGlobals::GDoNotCallStartAutoSaveProgress });
    }

    ImGui::Separator();
    ImGui::Text("Cheats");
    ImGui::Separator();
    ImGui::Checkbox("Infinite Health", &m_bGodMode);
    ImGui::Checkbox("Infinite Will", &m_bInfiniteWill);

    ImGui::Separator();
    ImGui::Text("Console");
    ImGui::Separator();
    ImGui::InputFloat("Trading Price Multiplier", CTCAIScratchPad::TradingPriceMult);

    if (ImGui::InputInt("Primitive Fade Distance", &NGlobalConsole::PrimitiveFadeDistance))
    {
        NGlobalConsole::ForcePrimitiveFadeDistance = (NGlobalConsole::PrimitiveFadeDistance > 0);
    }
    ImGui::InputFloat("Override Speed Multiplier", &NGlobalConsole::ConsoleOverrideMultiplier);
    ImGui::Checkbox("Debug Stress Test", &NGlobalConsole::GCombatStressTestDebug);
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

    CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer();
    if (plr)
    {
        CThing* t = plr->GetCharacterThing();
        ImGui::Text("Player Stats: 0x%X", t->GetTC(TCI_HERO_STATS));
        ImGui::Text("Player Morph: 0x%X\n", t->GetTC(TCI_APPEARANCE_MORPH));
        ImGui::Text("Player Experience: 0x%X\n", t->GetTC(TCI_HERO_EXPERIENCE));
        ImGui::Text("Player Thing: 0x%X\n", t);
        ImGui::Text("Player Physics: 0x%X\n", t->GetTC(TCI_PHYSICS));
        ImGui::Text("Player: 0x%X\n", plr);
        ImGui::Text("Draw: 0x%X\n", t->GetTC(TCI_GRAPHIC_APPEARANCE_NEW));
        ImGui::Text("Script Manager: 0x%X\n", wrld->GetScriptInfoManager());
    }
#endif
}

void FableMenu::DrawSettings()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.5f, 0.5f });
    ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
    ImGui::SetNextWindowSize({ 700,700 }, ImGuiCond_Once);
    ImGui::Begin("Settings", &m_bSubmenuActive[SM_Settings]);

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
        ImGui::InputFloat("##", &SettingsMgr->fMenuScale);
        ImGui::PopItemWidth();
        break;
    case INI:
        ImGui::TextWrapped("These settings control FableMenu.ini options. Any changes require game restart to take effect.");
        ImGui::LabelText("##", "Core");
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
            Notifications->SetNotificationTime(2500);
            Notifications->PushNotification("Keys reset! Remember to save.");
        }

        ImGui::Separator();
        ImGui::LabelText("##", "Core");
        ImGui::Separator();
        KeyBind(&SettingsMgr->iMenuOpenKey, "Open/Close Menu", "menu");
        ImGui::Separator();
        ImGui::LabelText("##", "Camera");
        ImGui::Separator();

        KeyBind(&SettingsMgr->iFreeCameraKeyForward, "Forward", "x_plus");
        KeyBind(&SettingsMgr->iFreeCameraKeyBack, "Back", "x_minus");
        KeyBind(&SettingsMgr->iFreeCameraKeyLeft, "Left", "y_plus");
        KeyBind(&SettingsMgr->iFreeCameraKeyRight, "Right", "y_minus");
        KeyBind(&SettingsMgr->iFreeCameraKeyUp, "Up", "z_plus");
        KeyBind(&SettingsMgr->iFreeCameraKeyDown, "Down", "z_minus");
        
        ImGui::Separator();
        ImGui::LabelText("##", "Action Keys");
        ImGui::Separator();
        GameKeyBind(&SettingsMgr->iHeroJumpKey, "Jump", "jump_action", GAME_ACTION_JUMP);
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
        Notifications->SetNotificationTime(2500);
        Notifications->PushNotification("Settings saved to FableMenu.ini and fablemenu_user.ini!");
        GUIImplementationDX9::RequestFontReload();
        SettingsMgr->SaveSettings();
    }

    ImGui::EndChild();
    ImGui::PopStyleVar();

    ImGui::End();
}

void FableMenu::DrawCreatureList()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.5f, 0.5f });
    ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
    ImGui::SetNextWindowSize({ 700,700 }, ImGuiCond_Once);
    ImGui::Begin("Creature List", &m_bSubmenuActive[SM_Creature_List]);

    static ImGuiTextFilter filter;
    ImGui::TextWrapped("Click on any entry to copy to clipboard.");
    ImGui::Text("Search");
    ImGui::PushItemWidth(-FLT_MIN);
    filter.Draw("##wclist");
    ImGui::PopItemWidth();

    ImGui::BeginChild("##list", { 0, -ImGui::GetFrameHeightWithSpacing() }, true);

    static int selectID = 0;
    for (int n = 0; n < IM_ARRAYSIZE(szCreatureList); n++)
    {
        if (filter.PassFilter(szCreatureList[n]))
        {
            bool is_selected = (selectID == n);
            if (ImGui::Selectable(szCreatureList[n], is_selected))
            {
                selectID = n;

                char name[256] = {};
                sprintf(name, "%s", szCreatureList[selectID]);
                CopyToClipboard(name);
            }
        }
    }

    ImGui::EndChild();
    ImGui::PopStyleVar();

    ImGui::End();
}

void FableMenu::DrawObjectList()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.5f, 0.5f });
    ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
    ImGui::SetNextWindowSize({ 700,700 }, ImGuiCond_Once);
    ImGui::Begin("Object List", &m_bSubmenuActive[SM_Object_List]);

    static ImGuiTextFilter filter;
    ImGui::TextWrapped("Click on any entry to copy to clipboard.");
    ImGui::Text("Search");
    ImGui::PushItemWidth(-FLT_MIN);
    filter.Draw("");
    ImGui::PopItemWidth();

    ImGui::BeginChild("##olist", { 0, -ImGui::GetFrameHeightWithSpacing() }, true);

    static int selectID = 0;
    for (int n = 0; n < IM_ARRAYSIZE(szObjectsList); n++)
    {
        if (filter.PassFilter(szObjectsList[n]))
        {
            bool is_selected = (selectID == n);
            if (ImGui::Selectable(szObjectsList[n], is_selected))
            {
                selectID = n;

                char name[256] = {};
                sprintf(name, "%s", szObjectsList[selectID]);
                CopyToClipboard(name);

            }
        }
    }

    ImGui::EndChild();
    ImGui::PopStyleVar();

    ImGui::End();
}

void FableMenu::DrawParticleList()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.5f, 0.5f });
    ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
    ImGui::SetNextWindowSize({ 700,700 }, ImGuiCond_Once);
    ImGui::Begin("Particle List", &m_bSubmenuActive[SM_Particle_List]);

    static ImGuiTextFilter filter;
    ImGui::TextWrapped("Click on any entry to copy to clipboard.");
    ImGui::Text("Search");
    ImGui::PushItemWidth(-FLT_MIN);
    filter.Draw("");
    ImGui::PopItemWidth();

    ImGui::BeginChild("##plist", { 0, -ImGui::GetFrameHeightWithSpacing() }, true);

    static int selectID = 0;
    for (int n = 0; n < IM_ARRAYSIZE(szParticleList); n++)
    {
        if (filter.PassFilter(szParticleList[n]))
        {
            bool is_selected = (selectID == n);
            if (ImGui::Selectable(szParticleList[n], is_selected))
            {
                selectID = n;

                char name[256] = {};
                sprintf(name, "%s", szParticleList[selectID]);
                CopyToClipboard(name);
            }
        }
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

void FableMenu::GameKeyBind(int* var, char* bindName, char* name, EGameAction action)
{
    CUserProfileManager* profile = CUserProfileManager::Get();
    CActionInputControl input;
    profile->GetAssignedInputForAction(action, !FGlobals::GUsePassiveAggressiveMode, &input);

    if (gameKeyCodes[input.KeyboardKey] != *var)
    {
        EInputKey key = eKeyboardMan::GetInputFromVKKeyCode(*var);
        
        if (key)
        {
            profile->SetAssignedInputKeyboard(action, key, !FGlobals::GUsePassiveAggressiveMode);
        }
    }
    else
    {
        *var = gameKeyCodes[input.KeyboardKey];
    }

    ImGui::LabelText("", bindName);
    DrawKeyBind(name, var);
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
        CBulletTimeManager* time = wrld->GetBulletTime();
        if (wrld->isLoadRegion())
        {
            for (CThing* thing : FableMenu::m_vAttachedParticles)
            {
                if (thing->isThingAlive())
                {
                    CTCDParticleEmitter* attached = (CTCDParticleEmitter*)thing->GetTC(TCI_PARTICLE_EMITTER);
                    attached->ClearAttachments();
                }
            }
            FableMenu::m_vAttachedParticles.clear();
            FableMenu::m_vCreatedParticles.clear();

            if (FableMenu::ms_bSlowmotion && time->m_bActive)
                time->m_bActive = 0;
        }
        else
        {
            if (FableMenu::ms_bSlowmotion && !time->m_bActive)
				time->m_bActive = 1;
        }

        CPlayer* plr = CMainGameComponent::Get()->GetPlayerManager()->GetMainPlayer();
        if (plr)
        {
            CThing* t = plr->GetCharacterThing();

            if (TheMenu->m_bIsActive && !TheMenu->m_bFrozeControls)
            {
                plr->DisableInput();
                TheMenu->m_bFrozeControls = true;
            }
            else if (!TheMenu->m_bIsActive && TheMenu->m_bFrozeControls)
            {
                plr->EnableInput();
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
                if (t)
                {
                    CTCHeroStats* stats = (CTCHeroStats*)t->GetTC(TCI_HERO_STATS);
                    stats->m_nStamina = 10000;
                }
            }

            if (TheMenu->m_bCustomCameraPos && TheMenu->ms_bFreeCam && TheMenu->m_nFreeCameraMode == FREE_CAMERA_CUSTOM)
                FreeCamera::Update();
        }
    }
}

void HookRegularUpdate()
{
    if (!InGame())
        return;

    CWorld* wrld = CMainGameComponent::Get()->GetWorld();

    if (wrld)
    {
        if (wrld->isLoadSave()) {
            FableMenu::ms_bDisableCreateParticle = true;
            FableMenu::m_vCreatedParticles.clear();
            FableMenu::m_vAttachedParticles.clear();
        }
        else if (FableMenu::ms_bDisableCreateParticle) {
            FableMenu::ms_bDisableCreateParticle = false;
        }
    }
}

void FableMenu::TakeActionItem(CThing* creature, char* objectName)
{
    int id = CThing::GetThingID(objectName);
    CThing* thing = CreateThing(id, creature->GetPosition(), 0, 0, 0, (char*)"thing");
    CTCBase* base = (CTCBase*)GameMalloc(100);
    CTCBase* action = (CTCBase*)GameMalloc(180);

    creature->ClearQueuedActions();
    creature->FinishCurrentAction();

    if (objectName == "OBJECT_VILLAGE_TAVERN_JUG")
        new CCreatureAction_PickUpJugToFill((CCreatureAction_PickUpJugToFill*)action, creature, thing);
    else if (objectName == "OBJECT_CRATE_SMALL_EXPLOSIVE_01_USABLE")
        new CCreatureAction_PickUpGenericBox((CCreatureAction_PickUpGenericBox*)action, creature, thing);
    creature->SetCurrentAction(action);
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

bool IsWindowFocused()
{
    return TheMenu->m_bIsFocused;
}

char* GetUTF8String(wchar_t* name)
{
    char utf8Buff[256] = {};
    int size = WideCharToMultiByte(CP_UTF8, 0, name, -1, NULL, 0, NULL, NULL);

    WideCharToMultiByte(CP_UTF8, 0, name, -1, utf8Buff, size, NULL, NULL);

    return utf8Buff;
}

void CopyToClipboard(char* name)
{
    const size_t len = strlen(name) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), name, len);
    GlobalUnlock(hMem);
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    Notifications->SetNotificationTime(2500);
    Notifications->PushNotification("Copied %s to clipboard!", name);
}