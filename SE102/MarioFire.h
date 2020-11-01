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
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

