#include "MagicObject.h"
#include "Mario.h"
#include "QuestionBrick.h"

CMagicObject::CMagicObject(float x, float y) : CGameObject()
{
	this->x = x;
	this->y = y;
	yStart = y;
	SetState(MAGICOBJECT_STATE_MUSHROOM);
}

void CMagicObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + MAGICOBJECT_BBOX_WIDTH;
	top = y;
	bottom = y + MAGICOBJECT_BBOX_HEIGHT;
}

void CMagicObject::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (state != MAGICOBJECT_STATE_DIE)
	{
		if (Actively == 1)
		{
			if (nxCollision < 0)
			{
				vx = -vx;
			}
			else
				SetState(MAGICOBJECT_STATE_DIE);
		}
	}
	if(Actively==0)
	{
		CMario* mario = (CMario*)coObj;
		mario->SwitchType(2);
		SetState(MAGICOBJECT_STATE_DIE);
	}
}

void CMagicObject::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (state != MAGICOBJECT_STATE_DIE)
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
		SetState(MAGICOBJECT_STATE_DIE);
	}
}

void CMagicObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == MAGICOBJECT_STATE_MUSHROOM)
	{
		if (y >= yStart - MAGICOBJECT_BBOX_HEIGHT)
		{
			y -= 2;
			return;
		}
		else SetState(MAGICOBJECT_STATE_MUSHROOM_X);
	}
	vy += MAGICOBJECT_GRAVITY * dt;
	//vx = MAGICOBJECT_SPEED;
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
}

void CMagicObject::Render()
{
	string ani;
	if (state == MAGICOBJECT_STATE_LEAF)
		ani = MAGICOBJECT_ANI_LEAF;
	else if (state == MAGICOBJECT_STATE_MUSHROOM || state == MAGICOBJECT_STATE_MUSHROOM_X)
	{
		ani = MAGICOBJECT_ANI_MUSHROOM;
	}
	LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
	if (anim != NULL)
		anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	RenderBoundingBox();
}

void CMagicObject::SetState(int state)
{
	switch (state)
	{
	case MAGICOBJECT_STATE_LEAF:
		break;
	case MAGICOBJECT_STATE_MUSHROOM:
		this->state = state;
		break;
	case MAGICOBJECT_STATE_MUSHROOM_X:
		vx = MAGICOBJECT_SPEED;
		this->state = state;
		break;
	case MAGICOBJECT_STATE_DIE:
		this->isHidden = true;
		this->state = state;
		break;
	default:
		break;
	}
}