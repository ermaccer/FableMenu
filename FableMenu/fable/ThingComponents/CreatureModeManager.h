#pragma once
#include "Base.h"
#include "../Creature.h"

class CTCCreatureModeManager : public CTCBase {
public:
    CTCBase* GetCurrentCreatureMode();
    void SetupDefaultMode();
    void RemoveAllModes();
    void RemoveMode(NCreatureMode::EMode mode);
    void ResetModes();
    bool IsModeActive(NCreatureMode::EMode mode);
    bool AddMode(NCreatureMode::EMode mode);
};