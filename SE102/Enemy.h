#pragma once
#include "GameObject.h"
#include "EnemyConst.h"

enum class EnemyType
{
	GOOMBA,
	KOOPAS,
	GREEN_KOOPAS,
	GREEN_PARATROOPA,
	PARA_GOOMBA,
	RED_VENUS,
	GREEN_VENUS,
	BULLET,
	PIRANHA_PLANT,
};

enum class EnemyState
{
	VIP,
	LIVE,
	JUMP,
	FLY,
	BEING_ATTACKED,
	BEING_HELD,
	BEING_KICK,
	WILL_DIE,
	DIE,
	ATTACK,
	GOING_UP,
	IDLE_UP,
	GOING_DOWN,
	IDLE_DOWN,
	ACTION,
};

class CEnemy : public CGameObject
{
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	DWORD beginState = 0;
	DWORD timeState = 0;
	EnemyType eType;
	EnemyState eState;

	float eGravity = DEFAULT_GRAVITY;
	Vector2 vectorSize = Vector2(0, 0);
	DWORD timeWillDie = 0;

public:
	CEnemy(float x, float y);
	virtual float GetGravity() { return eGravity; }
	virtual float GetSpeed_LIVE_X() { return DEFAULT_SPEED_LIVE_X; }
	virtual float GetSpeed_LIVE_Y() { return 0.0f; }
	virtual DWORD GetTimeWillDie() { return timeWillDie; }
	virtual Vector2 GetSizeFromState(EnemyState state) { return vectorSize; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void SwitchState(EnemyState newState, DWORD timeNewState = 0);
	virtual void SetState(EnemyState newState, DWORD timeNewState = 0);
	virtual void SwitchType(EnemyType newType);

	virtual void AutoSwitchState() {};
	virtual void On_BEING_ATTACKED(int nxCollision);
	virtual void On_BEING_KICK(int nxCollision);
	virtual void On_BEING_HELD();
	virtual void On_JUMP();
	virtual void On_FLY();
	virtual void On_LIVE();
	virtual void On_ATTACK();

	virtual void ProcessState_LIVE();
	virtual void ProcessState_ACTION();
	virtual void ProcessState_ATTACK() {};
	virtual void ProcessState_BEING_ATTACKED() {};
	virtual void ProcessState_BEING_KICK();
	virtual void ProcessState_BEING_HELD();
	virtual void ProcessState_JUMP() {};
	virtual void ProcessState_FLY() {};
	virtual void ProcessState_WILL_DIE();
	virtual void ProcessState_DIE();
	virtual void NoCollision();
	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	virtual void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
	virtual string GetAnimationIdFromState();
	virtual EnemyState GetState() { return eState; }
};

