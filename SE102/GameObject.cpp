#include <d3dx9.h>
#include <algorithm>
#include "Utils.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObject.h"
#include "SpriteManager.h"
#include "PlatForm.h"
#include "Koopas.h"
#include "Goomba.h"
#include "ScenceManager.h"
#include "PlayScence.h"
#include <math.h>

#define MAX_VY			0.7f

#define BBoxId          "tex-bbox"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	isHidden = false;
}

void CGameObject::NoCollision(){
	x += dx;
	y += dy;
}

void CGameObject::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (Actively == 1) {
		coObj->CollisionX(this, nxCollision, 0);
	}
}

void CGameObject::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	
	if (Actively == 1) {
		if (nyCollision > 0) {
			this->vy = 0;
		}

		coObj->CollisionY(this, nyCollision, 0);
	}
}
void CGameObject::CollisionWithObj(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		NoCollision();
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGoomba*>(e->obj)) {
				int a = 0;
			}
			if (e->nx != 0)
			{
				if (abs((int)this->dt) < 10000)
					CollisionX(coEventsResult[i]->obj, nx);
			}
			if (e->ny != 0)
			{
				if (abs((int)this->dt) < 10000)
					CollisionY(e->obj, ny);
			}
		}

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;   
	dx = vx * dt;
	if (vy > MAX_VY) vy = MAX_VY;
	dy = vy * dt;
}

bool CGameObject::isInScreen()
{
	Vector2 camPos = CGame::GetInstance()->camera->GetCamPosition();
	if (this->x < camPos.x-100 || this->y < camPos.y ||
		this->x > CGame::GetInstance()->GetScreenWidth() + camPos.x +100
		|| this->y > CGame::GetInstance()->GetScreenHeight() + camPos.y)
		return false;
	return true;
}

bool CGameObject::HasOverLap(Vector2 l1, Vector2 r1, Vector2 l2, Vector2 r2) {
	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;

	// If one rectangle is above other 
	if (l1.y >= r2.y || l2.y >= r1.y)
		return false;

	return true;
}

void CGameObject::OnHadCollided(LPGAMEOBJECT coObj) {
	
}

LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	
	if (ml < mr && mt < mb && sl != sr && st != sb) {
		if (
			HasOverLap(Vector2(ml, mt), Vector2(mr, mb), Vector2(sl, st), Vector2(sr, sb))
			) {

			coO->OnHadCollided(this);
			this->OnHadCollided(coO);
		}
	}

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		

		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare); 
}


void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			if (dynamic_cast<CPlatForm*>(c->obj)) {

			}
			else {
				min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			}
			
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]); 
}


void CGameObject::RenderBoundingBox()
{
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(BBoxId);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	
	rect.left = 0;
	rect.top = 0;
	rect.right = r-l;
	rect.bottom = b-t;
	

	CGame::GetInstance()->Draw(l, t, bbox, rect.left, rect.top, rect.right, rect.bottom,Vector2(1,1), 120);
}
vector<LPGAMEOBJECT> CGameObject::SetObjectCollision()
{
	vector<LPGAMEOBJECT> obj;
	string currentScenceId = CGame::GetInstance()->GetCurrentSceneId();
	CPlayScene* s = (CPlayScene*)CScences::GetInstance()->Get(currentScenceId);
	LPGAMEOBJECT player = s->GetPlayer();
	obj.push_back(player);
	return obj;
}

CGameObject::~CGameObject()
{

}