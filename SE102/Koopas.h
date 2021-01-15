#pragma once

#include "Enemy.h"
#include "EnemyConst.h"


class CKoopas : public CEnemy
{
public:
	CKoopas(float x, float y);
	virtual string GetAnimationIdFromState();
	virtual Vector2 GetSizeFromState(EnemyState state) override;
	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	virtual void AutoSwitchState() override;
	virtual virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};