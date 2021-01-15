#pragma once

#include "Enemy.h"
#include "EnemyConst.h"


class CKoopas : public CEnemy
{
public:
	CKoopas(float x, float y);
	string GetAnimationIdFromState();
	Vector2 GetSizeFromState(EnemyState state) override;
	void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	void AutoSwitchState() override;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};