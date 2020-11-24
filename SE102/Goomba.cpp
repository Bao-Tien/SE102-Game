#include "Goomba.h"
#include "FireBullet.h"
#include "Mario.h"

CGoomba::CGoomba(float x, float y)
{
	this->x = x;
	this->y = y;
	SetState(GOOMBA_STATE_WALKING);
	this->isHidden = false;
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_WILL_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else 
	if (state == GOOMBA_STATE_DIE || state == GOOMBA_STATE_BEING_SHOOTED|| state == GOOMBA_STATE_WILL_DIE)
		top = left = right = bottom = 0;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::NoCollision()
{
	CGameObject::NoCollision();
}
void CGoomba::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (this->state != GOOMBA_STATE_DIE)
	{
		if (Actively == 1)
		{
			vx = -vx;
		}
		else
		{
			//if (dynamic_cast<CMario*>(coObj))
			//{
				CMario* mario = (CMario*)coObj;
				if (mario->mState == EMarioState::ATTACK)
					SetState(GOOMBA_STATE_BEING_SHOOTED, nxCollision);
			//}
		}
	}
	
	
}
void CGoomba::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (this->state != GOOMBA_STATE_DIE)
	{
		if (Actively == 1)
		{
			vy = 0;
		}
		else if (dynamic_cast<CMario*>(coObj))
		{
			SetState(GOOMBA_STATE_WILL_DIE);
		}
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += GOOMBA_GRAVITY * dt;
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
	/*vector<LPCOLLISIONEVENT> coEvents;
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

		if (nx != 0) vx = -vx;

		if (ny < 0) {
			vy = 0;
		}
	}*/
	if (state == GOOMBA_STATE_WILL_DIE && GetTickCount() - beginStateDie > 400)
	{
		SetState(GOOMBA_STATE_DIE);
	}
}

void CGoomba::Render()
{
	string ani = GOOMBA_ANI_WALK;
	if (state == GOOMBA_STATE_WILL_DIE) {
		ani = GOOMBA_ANI_DIE;
		LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
		if (anim != NULL)
			anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));

	}
	else if (state == GOOMBA_STATE_BEING_SHOOTED)
	{
		ani = GOOMBA_ANI_IDLE;
			LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
			if (anim != NULL)
				anim->Render(x, y, D3DXVECTOR2(1.0f, -1.0f));
	}
	else CAnimations::GetInstance()->Get(ani)->Render(x, y);
	

	//RenderBoundingBox();
}

void CGoomba::SetState(int state, float nxCollision)
{
	switch (state)
	{
	case GOOMBA_STATE_WILL_DIE: //bi thap xuong
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE;
		vx = 0;
		vy = 0;
		beginStateDie = GetTickCount();
		this->state = state;
		break;
	case GOOMBA_STATE_BEING_SHOOTED:
		if (nxCollision < 0)
		{
			vx = GOOMBA_BEING_SHOOTED_SPEED_X;
		}
		else vx = -GOOMBA_BEING_SHOOTED_SPEED_X;
		vy = -GOOMBA_BEING_SHOOTED_SPEED_Y;
		this->state = state;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		this->state = state;
		break;
	case GOOMBA_STATE_DIE:
		vx = 0;
		vy = 0;
		this->isHidden = true; // roi ma tai sao van renden goomba bi roi xuong
		this->state = state;
		break;
	}
}
