#pragma once
#include "Enemy.h"
#include "EnemyConst.h"
#include "Bullet_Venus.h"

class CRed_Venus : public CEnemy
{
protected:
	CBullet_Venus* bullet;
	int yStart;
	
public:
	CRed_Venus(float x, float y);
	virtual string GetAnimationIdFromState();
	virtual Vector2 GetSizeFromState(EnemyState state) override;
	virtual void AutoSwitchState() override;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual int GetnxFromMario();
	virtual void SetBullet();
	virtual CBullet_Venus* GetBullet() { return bullet; }
	void On_BEING_ATTACKED(int nxCollision);
};

