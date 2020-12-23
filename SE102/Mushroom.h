#pragma once
#include "GameObject.h"

//#define MAGICOBJECT_ANI_LEAF "ani-super-leaf-red"
#define MUSHROOM_ANI "ani-super-mushroom"

//#define MAGICOBJECT_STATE_LEAF 200
#define MUSHROOM_STATE 210 
#define MUSHROOM_STATE_X 211 
#define MUSHROOM_STATE_DIE 220 

#define MUSHROOM_SPEED 0.05f*2
#define MUSHROOM_GRAVITY 0.006f

#define MUSHROOM_BBOX_WIDTH  48
#define MUSHROOM_BBOX_HEIGHT  48

class CMushRoom : public CGameObject
{
private:
	
	float yStart;
	int state;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CMushRoom(float x, float y);
	void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively) override;
	void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively) override;
	void SetState(int state);
};

