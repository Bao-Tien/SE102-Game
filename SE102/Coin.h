#pragma once
#include "CollisionBox.h"

#define COIN_STATE_AFTER_COLLISION 112
#define COIN_STATE_NORMAL 111

#define COIN_ANI_NORMAL               "ani-coin"

class CCoin :public CCollisionBox
{
private:
	int state;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:

	CCoin(float x, float y, float width, float height);
	void GetBoundingBox(float& l, float& t, float& r, float& b) override;
	void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
	void SetState(int state);
};

