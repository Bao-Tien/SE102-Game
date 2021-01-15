#pragma once
#include "Enemy.h"
#include "EnemyConst.h"



class CPara_Goomba : public CEnemy
{
	int level = 2;
	
public:
	CPara_Goomba(float x, float y);
	string GetAnimationIdFromState();
	Vector2 GetSizeFromState(EnemyState state) override;
	void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
	void AutoSwitchState() override;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};

