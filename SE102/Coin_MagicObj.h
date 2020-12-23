#pragma once
#include "GameObject.h"

#define COIN_STATE_MAGICOBJECT 114
#define COIN_STATE_DIE 115

#define COIN_ANI_NORMAL               "ani-coin"
#define COIN_SPEED_Y				0.49f
#define COIN_BBOX_WIDTH 48
#define COIN_BBOX_HEIGHT 48

class CCoin_MagicObj : public CGameObject
{
private:
	int state;
	DWORD beginState = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CCoin_MagicObj(float x, float y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
	void SetState(int state);
};

