#include "GraphicAppearance.h"
#include "../../core.h"

void CTCGraphicAppearance::SetAsHighlighted(float width_world_space, float width_screen_space, int* col, 
	bool effect_carried_items, int effect_weapons, EAppearanceMeshEffectPriority priority, void* key)
{
	CallMethod<0x4C04C0, CTCGraphicAppearance*, float, float, int*, bool, int, EAppearanceMeshEffectPriority, void*>(this, width_world_space, width_screen_space, col, effect_carried_items, effect_weapons, priority, key);
}

void CTCGraphicAppearance::SetAlpha(unsigned int alpha)
{
	CallMethod<0x4BFAC0, CTCGraphicAppearance*, unsigned int>(this, alpha);
}

void CTCGraphicAppearance::ClearHighlighted(void* key)
{
	CallMethod<0x4BFFC0, CTCGraphicAppearance*, void*>(this, key);
}

void CTCGraphicAppearance::SetScale(float scale)
{
	CallMethod<0x4BFA50, CTCGraphicAppearance*, float>(this, scale);
}

void CTCGraphicAppearance::SetLightingChannel(CThing* channel, bool effect_carried_items, int effect_weapons)
{
	CallMethod<0x4BFB40, CTCGraphicAppearance*, CThing*, bool, int>(this, channel, effect_carried_items, effect_weapons);
}

void CTCGraphicAppearance::SetColor(int* color, void* key)
{
	CallMethod<0x4C00B0, CTCGraphicAppearance*, int*, void*>(this, color, key);
}