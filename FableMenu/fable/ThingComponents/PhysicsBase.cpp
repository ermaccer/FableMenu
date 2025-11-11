#include "PhysicsBase.h"
#include "../../core.h"

CVector* CTCPhysicsStandard::GetPosition()
{
    return (CVector*)((char*)this + 0xC);
}

CVector* CTCPhysicsStandard::GetVelocity()
{
    return (CVector*)((char*)this + 0x88);
}

RHSet* CTCPhysicsStandard::GetRHSet()
{
    return CallMethodAndReturn<RHSet*, 0x724BD0, CTCPhysicsStandard*>(this);
}

void CTCPhysicsStandard::SetPosition(CVector* position)
{
    CallMethod<0x726750, CTCPhysicsStandard*, CVector*>(this, position);
}

void CTCPhysicsStandard::EnablePhysics(bool enable)
{
    CallMethod<0x723630, CTCPhysicsStandard*>(this, enable);
}

void CTCPhysicsStandard::EnableGravity(bool enable)
{
    CallMethod<0x7235E0, CTCPhysicsStandard*>(this, enable);
}

bool CTCPhysicsStandard::IsCollisionEnabled()
{
    return (*((unsigned char*)this + 0x84) & 1);
}

bool CTCPhysicsStandard::IsGravityEnabled()
{
    return (*((unsigned char*)this + 0x84) & 4);
}

bool CTCPhysicsStandard::IsPhysicsEnabled()
{
    return (*((unsigned char*)this + 0x85) & 4);
}