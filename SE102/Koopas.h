#pragma once

#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.08f;
#define KOOPAS_GRAVITY 0.006f

#define KOOPAS_BEING_SHOOTED_SPEED_X 0.25f*2
#define KOOPAS_BEING_SHOOTED_SPEED_Y 0.65f*2

#define KOOPAS_BBOX_WIDTH 16*3
#define KOOPAS_BBOX_HEIGHT 26*3
#define KOOPAS_BBOX_HEIGHT_COUCH 16*3

#define KOOPAS_STATE_LIVE 100
#define KOOPAS_STATE_COUCH 200
#define KOOPAS_STATE_BEING_ATTACK 201
#define KOOPAS_STATE_BEING_SHOOTED 202
#define KOOPAS_STATE_DIE 203


#define KOOPAS_ANI_WALKING "ani-red-koopa-troopa-move"
#define KOOPAS_ANI_COUCH "ani-red-koopa-troopa-crouch"

class CKoopas : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int state;
	DWORD beginStateDie;
public:
	CKoopas(float x, float y);
	virtual void SetState(int state, float nxCollision = 1);
	virtual int GetState() { return state; }
};