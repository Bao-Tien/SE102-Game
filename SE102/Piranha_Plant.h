#pragma once
#include "Enemy.h"
//idle down - going up- idle up - going down
class CPiranha_Plant : public CEnemy
{
protected:
	int yStart;

public:
	CPiranha_Plant(float x, float y);
	virtual string GetAnimationIdFromState();
	virtual Vector2 GetSizeFromState(EnemyState state) override;
	virtual void AutoSwitchState() override;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void On_BEING_ATTACKED(int nxCollision);
};

