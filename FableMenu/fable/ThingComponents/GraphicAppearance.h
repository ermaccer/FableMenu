#pragma once
#include "../FCore.h"

class CThing;

enum EAppearanceMeshEffectPriority
{
    MESH_EFFECT_PRIORITY_NULL,
    MESH_EFFECT_PRIORITY_WEAPON_GLOWS,
    MESH_EFFECT_PRIORITY_SPELLS,
    MESH_EFFECT_PRIORITY_TARGETING,
    MESH_EFFECT_PRIORITY_SHIELD_SPELL_SPECIAL_OVERRIDE
};

class CTCGraphicAppearance
{
public:
	void SetAsHighlighted(float width_world_space, float width_screen_space, CRGBAColour* col, bool effect_carried_items, int effect_weapons, EAppearanceMeshEffectPriority priority, void* key);
    void ClearHighlighted(void* key);
    void SetAlpha(unsigned int alpha);
    void SetColor(CRGBAColour* color, void* key);
    void SetScale(float scale);
    void SetLightingChannel(CThing* channel, bool effect_carried_items, int effect_weapons);
};