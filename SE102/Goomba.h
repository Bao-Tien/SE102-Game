#pragma once
#include "Enemy.h"

#define GOOMBA_WALKING_SPEED 0.05f*2
#define GOOMBA_GRAVITY 0.006f

#define GOOMBA_BEING_ATTACKED_SPEED_X 0.25f*2
#define GOOMBA_BEING_ATTACKED_SPEED_Y 0.65f*2

#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 45
#define GOOMBA_BBOX_HEIGHT_DIE 27

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_BEING_SHOOTED 150
#define GOOMBA_STATE_WILL_DIE 200
#define GOOMBA_STATE_DIE 300

//#define GOOMBA_ANI_IDLE               "ani-goomba-idle"
//#define GOOMBA_ANI_DIE				  "ani-goomba-die"
//#define GOOMBA_ANI_WALK               "ani-goomba-walk"

class CGoomba : public CEnemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	//virtual void Render();

public:
	CGoomba(float x, float y);
	virtual void SetState(EnemyState state, float nx = 1);
	virtual string GetAnimationIdFromState();
};