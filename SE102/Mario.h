#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "MarioConst.h"

enum class EMarioType {
	SMALL,
	BIG,
	RACCOON,
	FIRE,
};

enum class EMarioState {
	IDLE,
	WALK,
	RUN,
	JUMP,
	FLY,
	FALL,
	FALL_SLIGHTLY,
	ATTACK,
	DIE,
	HOLD,
	REMEMBER,
};

class CMario : public CGameObject
{
protected:
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	float movementRatioX;
	
	float ax,ay;
	float f;

	DWORD beginState = 0;
	DWORD timeState = 0;
	int synergies;
public:
	EMarioType mType;
	EMarioState mState;
	CMario(float x = 0.0f, float y = 0.0f);
	virtual bool SwitchState(EMarioState newState, DWORD timeState = 0);
	virtual void SwitchType();
	virtual void SetState(EMarioState newState, DWORD timeState = 0);
	virtual void NoCollision();
	/*virtual void CollisionX(int nxCollision);
	virtual void CollisionY(int nyCollision);*/

	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively=1) override;
	virtual void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively=1) override;


	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	virtual void KeyboardHandle(int key, bool type);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual string GetAnimationIdFromState();

	void Reset();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};