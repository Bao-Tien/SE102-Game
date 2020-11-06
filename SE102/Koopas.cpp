#include "Koopas.h"

CKoopas::CKoopas(float x, float y)
{
	this->x = x;
	this->y = y;
	this->isHidden = false;
	
	SetState(KOOPAS_STATE_LIVE);
	
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_COUCH || state == KOOPAS_STATE_BEING_SHOOTED)
		bottom = y + KOOPAS_BBOX_HEIGHT_COUCH;

	else if (state == KOOPAS_STATE_BEING_ATTACK)
		left = top = right = bottom = 0;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isHidden) return;
	if (!this->isInScreen())return;
	vy += KOOPAS_GRAVITY * dt;
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
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

		if (nx != 0)
		{
			vx = -vx;
			this->nx = -this->nx;
		}

		if (ny < 0) {
			vy = 0;
			if (state == KOOPAS_STATE_BEING_ATTACK)
			{
				SetState(KOOPAS_STATE_DIE);
			}
		}
	}
	if (state == KOOPAS_STATE_COUCH && GetTickCount() - beginStateDie > 5000)
	{
		SetState(KOOPAS_STATE_LIVE);
		y += KOOPAS_BBOX_HEIGHT_COUCH - KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::Render()
{
	string ani = KOOPAS_ANI_WALKING;
	LPANIMATION anim = CAnimations::GetInstance()->Get(KOOPAS_ANI_WALKING);
	if (!this->isHidden) {
		if (state == KOOPAS_STATE_COUCH || state == KOOPAS_STATE_BEING_SHOOTED) {
			ani = KOOPAS_ANI_COUCH;
			CAnimations::GetInstance()->Get(ani)->Render(x,y);
			
		}
		else if (state == KOOPAS_STATE_BEING_ATTACK || state == KOOPAS_STATE_DIE)
		{
			ani = KOOPAS_ANI_COUCH;
			LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
			if (anim != NULL)
				anim->Render(x, y, D3DXVECTOR2(1.0f, -1.0f));
		}
		else
		{
			anim = CAnimations::GetInstance()->Get(ani);
			if (anim != NULL)
				if (nx == 1)
					anim->Render(x, y, D3DXVECTOR2(-1.0f, 1.0f));
				else anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
		}
	}


	RenderBoundingBox();
}

void CKoopas::SetState(int state, float nxCollision)
{
	switch (state)
	{
	case KOOPAS_STATE_COUCH:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_COUCH;
		vx = 0;
		vy = 0;
		beginStateDie = GetTickCount();
		this->state = state;
		break;
	case KOOPAS_STATE_LIVE:
		vx = -KOOPAS_WALKING_SPEED;
		nx = -1;
		this->state = state;
		break;
	case KOOPAS_STATE_BEING_ATTACK:
		if (nxCollision < 0)
		{
			vx = KOOPAS_BEING_SHOOTED_SPEED_X;
		}
		else vx = -KOOPAS_BEING_SHOOTED_SPEED_X;
		vy = -KOOPAS_BEING_SHOOTED_SPEED_Y;
		this->state = state;
		break;
	case KOOPAS_STATE_BEING_SHOOTED:
		if (nxCollision < 0)
		{
			vx = KOOPAS_BEING_SHOOTED_SPEED_X;
		}
		else vx = -KOOPAS_BEING_SHOOTED_SPEED_X;
		this->state = state;
		break;
	case KOOPAS_STATE_DIE:
		vx = 0;
		vy = 0;
		this->state = state;
		break;
	}

}