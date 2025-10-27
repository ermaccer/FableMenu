#pragma once
#include "../FCore.h"
#include "Base.h"

class CThing;

class CTCDParticleEmitter : public CTCBase {
public:
	CTCDParticleEmitter(CThing* thing);
	void AttachToThing(CThing* thing, CCharString attach_flags, CCharString* pos_name, int pos_index, float height_ffset);
	void AttachToCamera(int attach_flags,float height_offset);
	void SetAlwaysUpdate(bool always_update);
	void SetParticlePosition(CVector* position);
	void ClearAttachments();
	void KillParticle();
	static CThing* Create(int particle_type_id, CVector* pos, bool force);
};

class CParticleEmitterDatabase {
public:
	static CParticleEmitterDatabase* Get();
	int GetEmitterTemplateHandleFromName(CCharString* a2);
};