#include "ScriptedControl.h"
#include "../../core.h"

void CTCScriptedControl::AddAction(CActionBase* action)
{
    CallMethod<0x7137D0, CTCScriptedControl*, CActionBase*>(this, action);
}

void CTCScriptedControl::ClearAllActions()
{
    CallMethod<0x713630, CTCScriptedControl*>(this);
}