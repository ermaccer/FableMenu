#pragma once

class CTCHaste
{
public:
	char pad[0xC];
	float m_fMultiplier;

	float GetActionSpeedMultiplier();
	void SetActionSpeedMultiplier(void* pcaller, float multiplier);
	void UnsetActionSpeedMultiplier(void* pcaller);
};