#pragma once
#include "GameObject.h"

#define MAGICOBJECT_ANI_LEAF "ani-super-leaf-red"
#define MAGICOBJECT_ANI_BALL "ani-super-mushroom"

#define MAGICOBJECT_STATE_LEAF 200
#define MAGICOBJECT_STATE_BALL 210 
#define MAGICOBJECT_STATE_DIE 220 

#define MAGICOBJECT_SPEED 0.05f*2
#define MAGICOBJECT_GRAVITY 0.006f

#define MAGICOBJECT_BBOX_WIDTH  48
#define MAGICOBJECT_BBOX_HEIGHT  48

class CMagicObject : public CGameObject
{
private:
	int state;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:

	CMagicObject(float x, float y);
	void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
	void SetState(int state);
};

