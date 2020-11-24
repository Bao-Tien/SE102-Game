#pragma once
#include "Mario.h"
#include "FireBullet.h"


class CMarioFire : public CMario
{
	
public:
	vector<CFireBullet*> bullets;
	CMarioFire(float x = 0.0f, float y = 0.0f);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void KeyboardHandle(int key, bool type);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

