#pragma once
#include "GameObject.h"
#include "MarioConst.h"

#define MARIO_SELECTION_BBOX_WIDTH  20
#define MARIO_SELECTION_BBOX_HEIGHT 20

class CMarioSelectScence : public CGameObject
{
public:
	CMarioSelectScence(float x, float y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively = 1) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void KeyboardHandle(int key);


};

