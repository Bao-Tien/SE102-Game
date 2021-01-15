#include "Coin_MagicObj.h"

CCoin_MagicObj::CCoin_MagicObj(float x, float y) : CMagic_Object(x, y)
{
	On_ACTIVE();
}

string CCoin_MagicObj::GetAnimationIdFromType()
{
	return COIN_ANI_NORMAL;
}

Vector2 CCoin_MagicObj::GetSizeFromType()
{
	return Vector2(COIN_BBOX_WIDTH, COIN_BBOX_HEIGHT);
}

void CCoin_MagicObj::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	CGameObject::CollisionY(coObj, nyCollision, Actively);
	if (mgState != MagicState::DIE)
	{
		if (Actively == 1)
		{
			On_DIE();
		}
	}
}

void CCoin_MagicObj::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMagic_Object::Update(dt, coObjects);
}

