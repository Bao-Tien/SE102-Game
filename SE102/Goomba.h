#pragma once
#include "Enemy.h"
#include "EnemyConst.h"

class CGoomba : public CEnemy
{
public:
	CGoomba(float x, float y);
	string GetAnimationIdFromState();
	Vector2 GetSizeFromState(EnemyState state) override;
	void AutoSwitchState() override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
};