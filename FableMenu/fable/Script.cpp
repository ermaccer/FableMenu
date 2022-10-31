#include "Script.h"
#include "..\core.h"

void SetScriptStatus(CCharString* name, EScriptStatus status)
{
	FASTCall<0xCBFAB8, CCharString*, int>(name, status);
}

EScriptStatus GetScriptStatus(CCharString* name)
{
	int script = CallMethodAndReturn<int, 0xCD39B1, int, CCharString*>(0x143E910, name);
	if (script)
		return (EScriptStatus)(*(int*)script);
	return Script_Ignored;
}

int GetScript(CCharString* name)
{
	int script = CallMethodAndReturn<int, 0xCD39B1, int, CCharString*>(0x143E910, name);
	return script;
}

void CScriptInfoManager::AddScript(CScriptInfo* info, char* shortName)
{
	CallMethod<0xCB5C90, CScriptInfoManager*, CScriptInfo*, char*>(this, info, shortName);
}

void CScriptInfoManager::PrintAllScripts()
{
	for (int i = 0; i < 321; i++)
	{
		printf("%s\n", data[i].name->unk);
	}
}
