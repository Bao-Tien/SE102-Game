#include "Enemy.h"
#include "Mario.h"

CEnemy::CEnemy(float x, float y)
{
	this->x = x;
	this->y = y;
	beginState = 0;
	eState = EnemyState::LIVE;
	this->isHidden = false;
}

void CEnemy::NoCollision()
{
	CGameObject::NoCollision();
}
void CEnemy::CollisionX(LPGAMEOBJECT coObj, int nxCollision, int Actively)
{
	if (eState!=EnemyState::DIE)
	{
		if (Actively == 1)
		{
			vx = -vx;
		}
		else
		{
			/*if (dynamic_cast<CMario*>(coObj))
			{*/
			CMario* mario = (CMario*)coObj;
			if (mario->mState == EMarioState::ATTACK)
				SetState(EnemyState::BEING_ATTACKED, nxCollision);
			//}
		}
	}


}
void CEnemy::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	if (eState != EnemyState::DIE)
	{
		if (Actively == 1)
		{
			vy = 0;
		}
		else if (dynamic_cast<CMario*>(coObj))
		{
			SetState(EnemyState::WILL_DIE, nyCollision);
		}
	}
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
}

string CEnemy::GetAnimationIdFromState()
{
	return "ani-goomba-idle";
}

void CEnemy::Render()
{
	string ani = GetAnimationIdFromState();
	LPANIMATION anim = CAnimations::GetInstance()->Get(ani);
	if (anim != NULL)
	{
		if(eState == EnemyState::DIE)
			anim->Render(x, y, D3DXVECTOR2(1.0f, -1.0f));
		else anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	}
	//RenderBoundingBox();
}