#pragma once
#include "../FCore.h"
#include "../ThingCreature/ScriptedControl.h"

class CActionPlayAnimation : public CTCScriptedControl::CActionBase {
public:
	CActionPlayAnimation(CActionBase* CActionPlayAnimation, CCharString* AnimName, bool stay_on_last_frame, bool looping, int num_loops, bool use_movement, int priority, bool add_as_queued_action, bool wait_for_anim_to_finish, bool use_physics, bool anim_may_need_camera_position_updated_in_speak_and_wait, bool allow_looking);
};