#pragma once
#include "CollisionBox.h"
#include "SquareConst.h"

enum class SquareType
{
	QUESTION_BRICK,
	BRICK,
};

enum class SquareState
{
	NORMAL,
	AFTER_COLLISION,
	BROKEN,
	DIE,
};
class CSquare : public CCollisionBox
{
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	DWORD beginState = 0;
	DWORD timeState = 0;
	SquareType bType;
	SquareState bState;

	float bGravity = 0;
	Vector2 vectorSize = Vector2(0, 0);
	DWORD timeWillDie = 0;

public:
	CSquare(int x, int y, int width, int height);
	virtual float GetGravity() { return bGravity; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	virtual void SwitchState(SquareState newState, DWORD timeNewState = 0);
	virtual void SetState(SquareState newState, DWORD timeNewState = 0);

	virtual void AutoSwitchState() {};
	virtual void On_AFTER_COLLISION();
	virtual void On_BROKEN();
	virtual void ProcessState_BROKEN() {};
	virtual void NoCollision();
	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override {};
	virtual void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override {};
	virtual string GetAnimationIdFromState();
};

