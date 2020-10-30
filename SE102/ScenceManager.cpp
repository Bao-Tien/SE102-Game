#include "ScenceManager.h"
#include <d3d9.h>

CScences* CScences::__instance = NULL;

CScences::CScences(){} 

CScences* CScences::GetInstance()
{
	if (__instance == NULL) __instance = new CScences();
	return __instance;
	
}

void CScences::Add(std::string id, LPSCENE scence)
{
	scences[id] = scence;
}

LPSCENE CScences::Get(std::string id)
{
	return scences[id];
}

void CScences::Clear()
{
	for (auto x : scences)
	{
		LPSCENE s = x.second;
		delete s;
	}

	scences.clear();
}