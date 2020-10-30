#pragma once
#include "AnimationManager.h"
#include "Utils.h"

typedef vector<LPANIMATION> CAnimationSet;

typedef CAnimationSet* LPANIMATION_SET;

/*
	Manage animation set database
*/
class CAnimationSets
{
	static CAnimationSets* __instance;

	unordered_map<string, LPANIMATION_SET> animation_sets;

public:
	CAnimationSets();
	void Add(string id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(string id);


	static CAnimationSets* GetInstance();
};