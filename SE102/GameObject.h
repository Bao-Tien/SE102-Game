#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "SpriteManager.h"
#include "AnimationManager.h"
#include "AnimationSet.h"


using namespace std;

#define ID_TEX_BBOX "-100"		// special texture to draw object bounding box // hop gioi han doi tuong

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny; // nx : vector phap tuyen theo chieu x, ny : vector phap tuyen theo chieu y

	float dx, dy;		// *RELATIVE* movement distance between this object and obj  

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:
	string bboxId;

	float x;
	float y;

	float dx;	
	float dy;	

	float vx;
	float vy;

	int nx;

	DWORD dt; 

	LPANIMATION_SET animation_set;
	bool isHidden;
	float vxMax;

public:
	bool isInScreen();
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	virtual float GetvxMax() { return vxMax; }

	void RenderBoundingBox(); 

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; } 

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents); //Cac vat the co kha nang va cham vs this
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);  

	CGameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void NoCollision();
	virtual void CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively = 1) {};
	virtual void CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively = 1) ;


	virtual void CollisionWithObj(vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	
	~CGameObject();
};

