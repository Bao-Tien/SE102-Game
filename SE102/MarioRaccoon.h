#pragma once
#include "Mario.h"

class CMarioRaccoon : public CMario
{
	int beginFlying;
	
public:
	CMarioRaccoon(float x = 0.0f, float y = 0.0f);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void KeyboardHandle(int key, bool type);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};