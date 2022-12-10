#pragma once
#include "FCore.h"

enum EScriptStatus {
	Script_NotStarted,
	Script_InProgress,
	Script_Completed,
	Script_Failed,
	Script_Abandoned,
	Script_Ignored
};

class CScriptInfo {
public:
	int func;
	int masterFunc;
	CCharString Name;
	int id;
	bool isMaster;
};


struct CScriptInfoManager_Data {
	CCharString* name;
	int unk[2];
};

class CScriptInfoManager {
public:
	int unk;
	CScriptInfoManager_Data* data;
	void AddScript(CScriptInfo* info, CCharString* str);

	void PrintAllScripts();
};

void SetScriptStatus(CCharString* name, EScriptStatus status);
EScriptStatus GetScriptStatus(CCharString* name);
int GetScript(CCharString* name);