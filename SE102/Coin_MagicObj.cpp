#include "Coin_MagicObj.h"

CCoin_MagicObj::CCoin_MagicObj(float x, float y) : CGameObject()
{
	this->x = x;
	this->y = y;
	SetState(COIN_STATE_MAGICOBJECT);
}

void CCoin_MagicObj::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == COIN_STATE_DIE)
		top = left = right = bottom = 0;
	else
	{
		left = x;
		top = y;
		right = x + COIN_BBOX_WIDTH;
		bottom = y + COIN_BBOX_HEIGHT;
	}
}

void CCoin_MagicObj::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state == COIN_STATE_MAGICOBJECT && GetTickCount() - beginState > 100)
		SetState(COIN_STATE_DIE);
}

void CCoin_MagicObj::Render()
{
	string ani;
	if (state == COIN_STATE_MAGICOBJECT)
		ani = COIN_ANI_NORMAL;
	LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
	if (anim != NULL)
		anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));

	RenderBoundingBox();
}

void CCoin_MagicObj::SetState(int state)
{
	switch (state)
	{
	case COIN_STATE_MAGICOBJECT:
		vy = -COIN_SPEED_Y;
		beginState = GetTickCount();
		this->state = state;
		break;
	case COIN_STATE_DIE:
		this->state = state;
		break;
	default:
		break;
	}
}
