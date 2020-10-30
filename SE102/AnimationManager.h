#pragma once
#include "Animation.h"
//#include "tinystr.h"
//#include "tinyxml.h"

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<string, LPANIMATION> animations;

public:
	void Add(string id, LPANIMATION ani);
	LPANIMATION Get(string id);
	void Clear();
	void Initialization(string path);
	bool LoadAnimationFile(string path);
	static CAnimations* GetInstance();

};