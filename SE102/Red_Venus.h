#pragma once
#include "Enemy.h"
#include "EnemyConst.h"
#include "Bullet_Venus.h"

class CRed_Venus : public CEnemy
{
	CBullet_Venus* bullet;
	int yStart;
	
public:
	CRed_Venus(float x, float y);
	string GetAnimationIdFromState();
	Vector2 GetSizeFromState(EnemyState state) override;
	void AutoSwitchState() override;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int GetnxFromMario();
	void SetBullet();
	CBullet_Venus* GetBullet() { return bullet; }
};

