#include "Enemy.h"
#include "Mario.h"
#include "EnemyConst.h"
#include "Red_Goomba.h"
#include "PlayScence.h"
#include "Game.h"
#include "ScenceManager.h"


CEnemy::CEnemy(float x, float y)
{
	this->x = x;
	this->y = y;
	beginState = 0;
	this->isHidden = false;
}

bool CEnemy::SwitchType(EnemyType newType)
{
	if(newType == EnemyType::RED_GOOMBA)
		if (eType == EnemyType::PARA_GOOMBA)
		{
			CRed_Goomba* red_goomba = new CRed_Goomba(x, y);
			string currentScenceId = CGame::GetInstance()->GetCurrentSceneId();
			CPlayScene* s = (CPlayScene*)CScences::GetInstance()->Get(currentScenceId);
			s->AddObjToObjects_Enemy(red_goomba);
			return true;
		}
	return false;
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
			nx = -nx;
		}
	}


}
void CEnemy::CollisionY(LPGAMEOBJECT coObj, int nyCollision, int Actively)
{
	CGameObject::CollisionY(coObj, nyCollision, Actively);
	if (eState != EnemyState::DIE)
	{
		if (Actively == 1)
		{
			vy = 0;
		}
		else if (dynamic_cast<CMario*>(coObj))
		{
			SetState(EnemyState::WILL_DIE, nyCollision);
			SwitchType(EnemyType::RED_GOOMBA);
			CMario* mario = (CMario*)coObj;
			mario->MarioAfterCollisionYWithEnemy(); 
		}
	}
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!this->isInScreen())
		return;
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
		if(eState == EnemyState::BEING_ATTACKED)
			anim->Render(x, y, D3DXVECTOR2(1.0f, -1.0f));
		else 
			if( nx == 1)
				anim->Render(x, y, D3DXVECTOR2(-1.0f, 1.0f));
			else anim->Render(x, y, D3DXVECTOR2(1.0f, 1.0f));
	}
	RenderBoundingBox();
}
