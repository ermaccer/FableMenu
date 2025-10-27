#pragma once
#include "Base.h"

enum NCreatureMode;

class CTCCreatureModeManager : public CTCBase {
public:
    CTCBase* GetCurrentCreatureMode();
    void SetupDefaultMode();
    void RemoveAllModes();
    void RemoveMode(NCreatureMode mode);
    void ResetModes();
    bool isModeActive(NCreatureMode mode);
    bool AddMode(NCreatureMode mode);
};