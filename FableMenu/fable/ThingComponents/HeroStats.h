#pragma once
#include "Base.h"
#include "../FCore.h"

enum EHeroTrainingStatus
{
    TRAINING_STATUS_GRADUATED,
    TRAINING_STATUS_APPRENTICE,
    TRAINING_STATUS_BOY
};

class CTCHeroStats {
public:
    char pad[0x28];
    int m_nMorality;
    char _pad[0x2];
    float m_fAge;
    float m_fSunTan;
    float m_fFatness;
    int m_nMoney;
    int m_nMaxMoney;
    int m_nConfiscatedMoney;
    int m_nTotalMoneyEarned;
    int m_nTotalMoneySpent;
    int m_nRewardMoney;
    int m_RentMoney;
    int m_nStamina;
    int m_nMaxStamina;
    int m_nFramesUntilStaminaRefills;
    int m_nFramesUntilHealthRefills;
    int m_nScriptOverridePreventStaminaRefill;
    int m_nFramesUntilFatnessReduces;
    int m_nRenownLevel;
    int m_nRenownMaxLevel;
    int m_nRenownPointsInLevel;
    int m_nRenownTotal;
    float m_fAgreeableness;
    float m_fInherentAttractiveness;
    float m_fInherentScariness;
    float m_fExtraMaxHealth;
    float m_fExtraMaxStamina;
    int m_nFramesLeftForSpeedMultiplier;
    float m_fMaximumMultiplier;
    float m_fAttractiveness;
    float m_fScariness;
    float m_fAppearanceGoodstrength;
    float m_fSoundRadiusMultiplier;
    float m_fVisibilityMultiplier;
    int m_nFrameUpdatedClothingStats;
    int m_nFrameUpdatedTattooStats;
    int m_nNumFailedAQuest;
    int m_nNumCompletedAQuest;
    int m_nNumCompletedACoreQuest;
    int m_nNumCompletedAFeatQuest;
    int m_nNumCompletedAnOptionalQuest;
    int m_nNumBoastsTaken;
    int m_nNumBoastsCompleted;
    int m_nNumMountedTrophies;
    int m_nNumTrophyGamePlayed;
    int m_nBestTrophyWitnesses;
    int m_nNumberOfShopsOwned;
    int m_nNumberOfHousesOwned;
    int m_nNumberOfBuildingsRented;
    int m_nNumberOfVomits;
    int m_nNumberOfDrinks;
    int m_nNumberOfCrimes;
    int m_nNumberOfCrimesOfMurder;
    int m_nTotalFine;
    int m_nFinePaid;
    int m_nTimesThrownOut;
    int m_nTotalBribeAmount;
    int m_nNumTeleports;
    float m_fMaxChickenThrow;
    int m_nTrainingStatus;
    std::vector<long> m_vHeroStatsExperience;
    std::vector<long> m_vRegionTime;
    std::vector<long> m_vNumberOfTimesUsedAbility;
    int m_nTotalSpentExperience;
    int m_nNumLoversAcquired;
    int m_nNumWeddings;
    int m_nNumSpousesMurdered;
    int m_nNumSpousesDied;
    int m_nNumDivorces;
    int m_nNumSex;
    bool m_bHadScriptedSex;
    bool m_bHadScriptedGaySex;

    void CheckForNewExpressions();
};