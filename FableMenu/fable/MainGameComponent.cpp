#include "MainGameComponent.h"

CMainGameComponent* CMainGameComponent::Get()
{
    return *(CMainGameComponent**)(0x13B86A0);
}

CWorld* CMainGameComponent::GetWorld()
{
    return *(CWorld**)(this + 36);
}

CPlayerManager* CMainGameComponent::GetPlayerManager()
{
    return *(CPlayerManager**)(this + 28);
}
