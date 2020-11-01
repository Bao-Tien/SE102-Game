#pragma once
#include "GameObject.h"

#define FIRE_BULLET_WIDTH		30
#define FIRE_BULLET_HEIGHT		30
#define ANI_FIRE_BULLET			"ani-fire-bullet"
#define BULLET_GRAVITY			0.0006f
#define BULLET_SPEED_Y				0.3f


class CFireBullet: public CGameObject
{
	float ax = 0.010f * 3;
	int remember = 0;
public:
	CFireBullet(float x = 0.0f, float y = 0.0f);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

