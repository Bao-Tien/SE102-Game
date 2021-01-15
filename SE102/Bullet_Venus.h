#pragma once
#include "Enemy.h"
#include "EnemyConst.h"

class CBullet_Venus : public CEnemy
{
public:
	CBullet_Venus(float x, float y);
	string GetAnimationIdFromState();
	Vector2 GetSizeFromState(EnemyState state) override;
	void Collision(LPGAMEOBJECT, int);
	void CollisionX(LPGAMEOBJECT, int, int) override;
	void CollisionY(LPGAMEOBJECT, int, int) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>*) override;
};

