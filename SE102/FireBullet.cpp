#include "FireBullet.h"
#include "Game.h"

CFireBullet::CFireBullet(float x, float y)
{
	this->x = x;
	this->y = y;
	this->nx = nx;
	vy = 0;
	isHidden = true;
}

void CFireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	
	//dt = 20;
	vx += 0.03f * nx;
	vy += BULLET_GRAVITY * dt;
	CGameObject::Update(dt);

	// Simple fall down

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(colliable_objects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) {
			vx = 0;
			this->isHidden = true;
		}

		if (ny < 0) {
			vy = -BULLET_SPEED_Y;
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//ax = 0;
	
}

void CFireBullet::Render()
{
	int alpha = 255;

	LPANIMATION anim = CAnimations::GetInstance()->Get(ANI_FIRE_BULLET);
	if (anim != NULL)
	{
		if (nx < 0)
			anim->Render(x, y, D3DXVECTOR2(-1.0f, 1.0f), alpha);
		else anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f), alpha);
	}
	RenderBoundingBox();
}

void CFireBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIRE_BULLET_WIDTH;
	bottom = y + FIRE_BULLET_HEIGHT;
}