#pragma once
#include "Mario.h"

class CMarioRaccoon : public CMario
{

public:
	CMarioRaccoon(float x = 0.0f, float y = 0.0f);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};