#include "Magic_Object.h"
#include "Mario.h"

CMagic_Object::CMagic_Object(float x, float y)
{
	this->x = x;
	this->y = y;
	this->isHidden = false;
}

void CMagic_Object::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (mgState == MagicState::DIE)
	{
		left = top = right = bottom = 0;
		return;
	}
	left = x;
	top = y;
	right = x + GetSizeFromType().x;
	bottom = y + GetSizeFromType().y;
}

void CMagic_Object::SwitchState(MagicState newState, DWORD timeNewState)
{
	if (GetTickCount() - beginState >= timeState)
		SetState(newState, timeNewState);
}

void CMagic_Object::On_MOVE()
{
	vx = MUSHROOM_SPEED;
	SetState(MagicState::MOVE);
}

void CMagic_Object::On_ACTIVE()
{
	vy = -COIN_SPEED_Y;
	SetState(MagicState::ACTIVE);
}

void CMagic_Object::On_ACTIVE_OF_LEAF()
{
	vy = -LEAF_SPEED;
	SetState(MagicState::ACTIVE, LEAF_TIME_ACTIVE);
}
void CMagic_Object::On_LEFT()
{
	vx = -LEAF_SPEED_X;
}

void CMagic_Object::On_RIGHT()
{
	vx = LEAF_SPEED_X;
}

void CMagic_Object::On_DIE()
{
	vx = 0;
	vy = 0;
	this->isHidden = true;
	SetState(MagicState::DIE);
}

void CMagic_Object::NoCollision()
{
	CGameObject::NoCollision();
}

void CMagic_Object::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (mgState != MagicState::DIE)
	{
		if (Actively == 1)
		{
			if (nxCollision < 0)
			{
				vx = -vx;
			}
			else
				On_DIE();
		}
		else
		{
			if (dynamic_cast<CMario*>(coObj))
			{
				CMario* mario = (CMario*)coObj;
				mario->SwitchType(2);
				On_DIE();
			}
		}
	}
}

void CMagic_Object::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	CGameObject::CollisionY(coObj, nyCollision, Actively);
	if (mgState != MagicState::DIE)
	{
		if (Actively == 1)
		{
			vy = 0;
		}
		else
		{
			if (dynamic_cast<CMario*>(coObj))
			{
				CMario* mario = (CMario*)coObj;
				mario->SwitchType(2);
				On_DIE();
			}
		}
	}
}

void CMagic_Object::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += GetGravity() * dt;
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
	AutoSwitchState();
}

string CMagic_Object::GetAnimationIdFromType()
{
	return DEFINE_ANI;
}

void CMagic_Object::Render()
{
	string ani = GetAnimationIdFromType();
	LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
	if (anim != NULL)
	{
		anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	}
	RenderBoundingBox();
}

void CMagic_Object::SetState(MagicState newState, DWORD timeNewState)
{
	beginState = GetTickCount();
	timeState = timeNewState;
	mgState = newState;
}