#pragma once
#include "GameObject.h"

#define FIRE_BULLET_WIDTH		30
#define FIRE_BULLET_HEIGHT		30
#define ANI_FIRE_BULLET			"ani-fire-bullet"
#define BULLET_GRAVITY			0.0012f
#define BULLET_SPEED_X				0.3f
#define BULLET_SPEED_Y				0.44f
#define BULLET_STATE_ACTIVE    111
#define BULLET_STATE_NOACTIVE    112


class CFireBullet: public CGameObject
{
	int state;
public:
	CFireBullet(int nx, float x = 0.0f, float y = 0.0f);
	void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state , int nx = 1);
};

