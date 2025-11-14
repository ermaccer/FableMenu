#pragma once

class CThing;

class CTCScriptedControl {
public:
	class CActionBase {
	public:
		void SetThingToNotAvoid(CThing* thing);
	};

	void AddAction(CActionBase* action);
	void ClearAllActions();
};