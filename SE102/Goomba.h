#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.05f*2
#define GOOMBA_GRAVITY 0.006f

#define GOOMBA_BEING_SHOOTED_SPEED_X 0.25f*2
#define GOOMBA_BEING_SHOOTED_SPEED_Y 0.65f*2

#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 45
#define GOOMBA_BBOX_HEIGHT_DIE 27

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_BEING_SHOOTED 150
#define GOOMBA_STATE_WILL_DIE 200
#define GOOMBA_STATE_DIE 300

#define GOOMBA_ANI_IDLE               "ani-goomba-idle"
#define GOOMBA_ANI_DIE				  "ani-goomba-die"
#define GOOMBA_ANI_WALK               "ani-goomba-walk"

class CGoomba : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	DWORD beginStateDie = 0;
	int state;

public:
	CGoomba(float x, float y);
	virtual void SetState(int state, float nx = 1);
	virtual void NoCollision();
	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively);
	virtual void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively);
	virtual int GetState() { return state; }
};