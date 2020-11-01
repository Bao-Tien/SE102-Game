#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "MarioConst.h"


class CMario : public CGameObject
{
protected:
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
	bool isStanding ;
	bool isHighJump;
	bool isRunning;
	bool isAttack;
	float isFly;
	float ax,ay;
	float f;
	string ani;
public:
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};