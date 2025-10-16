#include "ParticleEmitter.h"
#include "../../core.h"

CTCDParticleEmitter::CTCDParticleEmitter(CThing* thing)
{
	CallMethod<0x6DFF30, CTCDParticleEmitter*, CThing*>(this,thing);
}

CThing* CTCDParticleEmitter::Create(int particle_type_id, CVector* pos, bool force)
{
	return FASTCallAndReturn<CThing*, 0x6E0880, int, CVector*,bool>(particle_type_id, pos, force);
}

void CTCDParticleEmitter::AttachToCamera(int attach_flags, float height_offset)
{
	CallMethod<0x6E0DB0, CTCDParticleEmitter*, int, float>(this, attach_flags, height_offset);
}

void CTCDParticleEmitter::SetParticlePosition(CVector* position)
{
	CallMethod<0x6E0500, CTCDParticleEmitter*, CVector*>(this, position);
}

void CTCDParticleEmitter::ClearAttachments()
{
	CallMethod<0x6E0AF0, CTCDParticleEmitter*>(this);
}

void CTCDParticleEmitter::KillParticle()
{
	CallMethod<0xAEE8C0, CTCDParticleEmitter*>(this);
}

void CTCDParticleEmitter::AttachToThing(CThing* thing, CCharString attach_flags, CCharString* pos_name, int pos_index, float height_offset)
{
	CallMethod<0x535290, CTCDParticleEmitter*, CThing*, CCharString, CCharString*, int, float>(this, thing, attach_flags, pos_name, pos_index, height_offset);
}

void CTCDParticleEmitter::SetAlwaysUpdate(bool always_update)
{
	CallMethod<0x6E0590, CTCDParticleEmitter*, bool>(this, always_update);
}

int CParticleEmitterDatabase::GetEmitterTemplateHandleFromName(CCharString* a2)
{
	return CallMethodAndReturn<int, 0xAE85B0, CParticleEmitterDatabase*, CCharString*>(this, a2);
}

CParticleEmitterDatabase* CParticleEmitterDatabase::Get()
{
	return CallAndReturn<CParticleEmitterDatabase*, 0xAEAAE0>();
}

