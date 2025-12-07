#pragma once
#include "Base.h"

enum eExperience 
{
    EXPERIENCE_STRENGTH,
    EXPERIENCE_SKILL,
    EXPERIENCE_WILL,
    TOTAL_EXPERIENCE
};

enum EHeroTitle
{
    TITLE_NONE,
    TITLE_REAPER,
    TITLE_SHADOWHUNTER,
    TITLE_MALEFICUS,
    TITLE_DEATHBRINGER,
    TITLE_ASSASSIN,
    TITLE_NECROMANCER,
    TITLE_AVATAR,
    TITLE_PILGRIM,
    TITLE_LIBERATOR,
    TITLE_PALADIN,
    TITLE_DRUID,
    TITLE_RANGER,
    TITLE_RUNEMASTER,
    TITLE_HOOD,
    TITLE_GLADIATOR,
    TITLE_SABRE,
    TITLE_ARROWDODGER,
    TITLE_PIEMASTER,
    TITLE_CHICKEN_CHASER,
    TITLE_ARSEFACE,
    TITLE_JACK,
    TITLE_MAZE,
    TITLE_SCARLET_ROBE,
    TITLE_SCYTHE,
    TITLE_THUNDER,
    TITLE_WHISPER,
    TITLE_TWINBLADE,
    TITLE_BRIAR_ROSE,
    TITLE_LADY_GREY,
    TITLE_GUILDMASTER,
    TITLE_SCORPION_SLAYER,
    TITLE_DEATH_BRINGER
};

class CTCHero : public CTCBase
{
public:
    bool m_bCanUseWeapons;
    bool m_bCanUseWill;
    bool m_bWeaponsUsable;
    EHeroTitle m_eTitle;
    char pad[0x30];
    CThing* attachedParticle;
    void SetTitle(int title_def_index);
};

class CTCHeroExperience : public CTCBase {
public:
    char pad[8];
    int  m_nGeneralExperience;
    int* m_pExperience;
};