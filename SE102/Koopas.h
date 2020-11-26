#pragma once

#include "Enemy.h"
#include "EnemyConst.h"


class CKoopas : public CEnemy
{
	/*virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int state;
	DWORD beginState;*/
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	CKoopas(float x, float y);
	/*virtual void NoCollision();
	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision);
	virtual void CollisionY(LPGAMEOBJECT coObj, int nyCollision);
	virtual void SetState(int state, float nxCollision = 1);
	virtual int GetState() { return state; }*/
	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	virtual void SetState(EnemyState state, float nxCollision = 1) override;
	virtual string GetAnimationIdFromState();
};