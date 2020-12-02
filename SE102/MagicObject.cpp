#include "MagicObject.h"
#include "Mario.h"

CMagicObject::CMagicObject(float x, float y) : CGameObject()
{
	this->x = x;
	this->y = y - MAGICOBJECT_BBOX_HEIGHT -20;
	SetState(MAGICOBJECT_STATE_BALL);
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
	int a = 9;
	if (Actively == 1)
	{
		if (nxCollision < 0)
		{
			vx = -vx;
		}
		else 
			SetState(MAGICOBJECT_STATE_DIE);
	}
	else
	{
		CMario* mario = (CMario*)coObj;
		mario->SwitchType(2);
		SetState(MAGICOBJECT_STATE_DIE);
	}
}

void CMagicObject::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (Actively == 1)
	{
		/*if (nyCollision < 0)
			vy = 0;*/
	}
	else
	{
		CMario* mario = (CMario*)coObj;
		mario->SwitchType(2);
		SetState(MAGICOBJECT_STATE_DIE);
	}
}

void CMagicObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += MAGICOBJECT_GRAVITY * dt;
	vx = MAGICOBJECT_SPEED;
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
}

void CMagicObject::Render()
{
	string ani;
	if (state == MAGICOBJECT_STATE_LEAF)
		ani = MAGICOBJECT_ANI_LEAF;
	else if(state == MAGICOBJECT_STATE_BALL)
		ani = MAGICOBJECT_ANI_BALL;
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
	case MAGICOBJECT_STATE_BALL:
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