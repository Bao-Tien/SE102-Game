#pragma once
#include "GameObject.h"
#include "MagicConst.h"

enum class MagicType
{
	MUSHROOM,
	LEAF,
	COIN_MAGIC,
};

enum class MagicState
{
	MOVE,
	ACTIVE,
	LEFT,
	RIGHT,
	DIE,
};

class CMagic_Object : public CGameObject
{
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	DWORD beginState = 0;
	DWORD timeState = 0;
	MagicType mgType;
	MagicState mgState;

	float mgGravity = DEFAULT_GRAVITY;
	Vector2 vectorSize = Vector2(0, 0);
	DWORD timeWillDie = 0;

public:
	CMagic_Object(float x, float y);
	virtual float GetGravity() { return mgGravity; }
	virtual Vector2 GetSizeFromType() { return vectorSize; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void SwitchState(MagicState newState, DWORD timeNewState = 0);
	virtual void SetState(MagicState newState, DWORD timeNewState = 0);

	virtual void AutoSwitchState() {};

	virtual void On_MOVE();
	virtual void On_ACTIVE();
	virtual void On_ACTIVE_OF_LEAF();
	virtual void On_LEFT();
	virtual void On_RIGHT();
	virtual void On_DIE();
	virtual void NoCollision();
	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	virtual void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
	virtual string GetAnimationIdFromType();
};

