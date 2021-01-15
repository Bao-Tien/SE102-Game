#include "Bullet_Venus.h"
#include "Mario.h"
#include "ScenceManager.h"
#include "PlayScence.h"
#include "Game.h"

CBullet_Venus::CBullet_Venus(float x, float y) : CEnemy(x, y)
{
	eType = EnemyType::BULLET;
	SetState(EnemyState::ACTION);
}

string CBullet_Venus::GetAnimationIdFromState()
{
	return BULLET_VENUS_ANI;
}

Vector2 CBullet_Venus::GetSizeFromState(EnemyState state)
{
	float width, height;
	width = BULLET_VENUS_WIDTH;
	height = BULLET_VENUS_HEIGHT;
	if (state == EnemyState::DIE)
	{
		height = 0;
		width = 0;
	}
	return Vector2(width, height);
}


void CBullet_Venus::Collision(LPGAMEOBJECT coObj, int Actively)
{
	if (Actively == 1)
	{
		if (dynamic_cast<CMario*>(coObj))
		{
			CMario* mario = (CMario*)coObj;
			if (eState == EnemyState::ACTION)
				mario->SwitchType(1);
		}
	}
}

void CBullet_Venus::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	Collision(coObj, Actively);
}

void CBullet_Venus::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	Collision(coObj, Actively);
}

void CBullet_Venus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = 0.4f * nx;
	vy = 0.4f;

	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);

}
