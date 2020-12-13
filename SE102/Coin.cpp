#include "Coin.h"

CCoin::CCoin(float x, float y, float width, float height) : CCollisionBox(x, y, width, height)
{
	SetState(COIN_STATE_NORMAL);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	CCollisionBox::GetBoundingBox(l, t, r, b);
	if (state == COIN_STATE_AFTER_COLLISION)
		l = t = r = b = 0;
}

void CCoin::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (Actively == 0)
	{
		SetState(COIN_STATE_AFTER_COLLISION);
	}
	else return;
}
void CCoin::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (Actively == 0)
	{
		if (nyCollision > 0)
			SetState(COIN_STATE_AFTER_COLLISION);
	}
	else return;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
}

void CCoin::Render()
{
	string ani;
	if (state == COIN_STATE_NORMAL)
		ani = COIN_ANI_NORMAL;
	LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
	if (anim != NULL)
		anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));


	RenderBoundingBox();
}

void CCoin::SetState(int state)
{
	switch (state)
	{
	case COIN_STATE_AFTER_COLLISION:
		this->state = state;
		break;
	case COIN_STATE_NORMAL:
		this->state = state;
		break;
	default:
		break;
	}
}
