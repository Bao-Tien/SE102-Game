#include "FireBullet.h"
#include "Game.h"
#include "Goomba.h"
#include "Koopas.h"

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
	if (this->isHidden) return;
	vx = BULLET_SPEED_X  * nx;
	vy += BULLET_GRAVITY * dt;
	CGameObject::Update(dt);


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

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
		
		for (int i = 0; i < coEventsResult.size(); i++)
		{
			if (dynamic_cast<CGoomba*>(coEventsResult[i]->obj))
			{
				((CGoomba*)(coEventsResult[i]->obj))->SetState(GOOMBA_STATE_BEING_SHOOTED, nx);
			}
			if (dynamic_cast<CKoopas*>(coEventsResult[i]->obj))
			{
				((CKoopas*)(coEventsResult[i]->obj))->SetState(KOOPAS_STATE_BEING_ATTACK, nx);
			}
		}

		if (nx != 0) {
			vx = 0;
			this->isHidden = true;
		}

		if (ny < 0) {
			vy = -BULLET_SPEED_Y;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (!this->isInScreen()) this->isHidden = true;
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
	//RenderBoundingBox();
}

void CFireBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIRE_BULLET_WIDTH;
	bottom = y + FIRE_BULLET_HEIGHT;
}