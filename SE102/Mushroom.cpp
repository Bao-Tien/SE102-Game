#include "MushRoom.h"
#include "Mario.h"
#include "QuestionBrick.h"

CMushRoom::CMushRoom(float x, float y) : CGameObject()
{
	this->x = x;
	this->y = y;
	yStart = y;
	SetState(MUSHROOM_STATE);
}

void CMushRoom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + MUSHROOM_BBOX_WIDTH;
	top = y;
	bottom = y + MUSHROOM_BBOX_HEIGHT;
}

void CMushRoom::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (state != MUSHROOM_STATE_DIE)
	{
		if (Actively == 1)
		{
			if (nxCollision < 0)
			{
				vx = -vx;
			}
			else
				SetState(MUSHROOM_STATE_DIE);
		}
	}
	if(Actively==0)
	{
		CMario* mario = (CMario*)coObj;
		mario->SwitchType(2);
		SetState(MUSHROOM_STATE_DIE);
	}
}

void CMushRoom::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (state != MUSHROOM_STATE_DIE)
	{
		if (Actively == 1)
		{
			vy = 0;
		}
	}
	
	if (Actively == 0)
	{
		CMario* mario = (CMario*)coObj;
		mario->SwitchType(2);
		SetState(MUSHROOM_STATE_DIE);
	}
}

void CMushRoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == MUSHROOM_STATE)
	{
		if (y > yStart - MUSHROOM_BBOX_HEIGHT)
		{
			y -= 2;
			return;
		}
		else SetState(MUSHROOM_STATE_X);
	}
	vy += MUSHROOM_GRAVITY * dt;
	//vx = MAGICOBJECT_SPEED;
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
}

void CMushRoom::Render()
{
	string ani;
	ani = MUSHROOM_ANI;
	LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
	if (anim != NULL)
		anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	RenderBoundingBox();
}

void CMushRoom::SetState(int state)
{
	switch (state)
	{
	case MUSHROOM_STATE:
		this->state = state;
		break;
	case MUSHROOM_STATE_X:
		vx = MUSHROOM_SPEED;
		this->state = state;
		break;
	case MUSHROOM_STATE_DIE:
		this->isHidden = true;
		this->state = state;
		break;
	default:
		break;
	}
}