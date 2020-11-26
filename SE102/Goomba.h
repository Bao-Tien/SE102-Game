#pragma once
#include "Enemy.h"
#include "EnemyConst.h"

class CGoomba : public CEnemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
	CGoomba(float x, float y);
	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	virtual void SetState(EnemyState state, float nxCollision = 1) override;
	virtual string GetAnimationIdFromState();
};