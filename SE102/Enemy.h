#pragma once
#include "GameObject.h"

enum class EnemyType
{
	GOOMBA,
	KOOPAS,
};

enum class EnemyState
{
	LIVE,
	BEING_ATTACKED,
	BEING_HELD,
	BEING_KICK,
	WILL_DIE,
	DIE,
};

class CEnemy : public CGameObject
{
protected:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	DWORD beginState = 0;
	EnemyType eType;
	EnemyState eState;

public:
	CEnemy(float x, float y);
	virtual void SetState(EnemyState state, float nxCollison = 1) {};
	virtual void NoCollision();
	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	virtual void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
	virtual string GetAnimationIdFromState();
	virtual EnemyState GetState() { return eState; }
};

