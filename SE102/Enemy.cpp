#include "Enemy.h"
#include "Mario.h"
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
	nx = -1;
}

void CEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (eState == EnemyState::DIE || eState == EnemyState::BEING_ATTACKED)
	{
		left = top = right = bottom = 0;
		return;
	}
	left = x;
	top = y;
	right = x + GetSizeFromState(eState).x;
	bottom = y + GetSizeFromState(eState).y;
}

void CEnemy::SwitchState(EnemyState newState, DWORD timeNewState)
{
	if (GetTickCount() - beginState >= timeState)
		SetState(newState, timeNewState);
}

void CEnemy::On_BEING_ATTACKED(int nxCollision)
{
	if (nxCollision < 0)
	{
		vx = DEFAULT_BEING_ATTACKED_SPEED_X;
	}
	else vx = -DEFAULT_BEING_ATTACKED_SPEED_X;
	vy = -DEFAULT_BEING_ATTACKED_SPEED_Y;
	SwitchState(EnemyState::BEING_ATTACKED);
}

void CEnemy::On_BEING_KICK(int nxCollision)
{
	nx = nxCollision * -1;
	SetState(EnemyState::BEING_KICK, DEFAULT_BEING_KICK_TIME);
}

void CEnemy::On_BEING_HELD()
{
	SetState(EnemyState::BEING_HELD, DEFAULT_BEING_KICK_TIME);
}

void CEnemy::On_JUMP()
{
	vy = -PARA_GOOMBA_JUMP_SPEED_Y * 1.5f;
	vx = nx * PARA_GOOMBA_FLY_SPEED_X;
	//SetState(EnemyState::JUMP, PARA_GOOMBA_TIME_JUMP);
}

void CEnemy::On_FLY()
{
	vy = -PARA_GOOMBA_FLY_SPEED_Y*1.3f;
	vx = nx * PARA_GOOMBA_JUMP_SPEED_X;
	//SetState(EnemyState::FLY, PARA_GOOMBA_TIME_FLY);
}

void CEnemy::On_LIVE()
{
	SetState(EnemyState::LIVE);
}

void CEnemy::On_ATTACK()
{

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
		else
		{
			if (eState != EnemyState::DIE)
			{
				if (dynamic_cast<CMario*>(coObj))
				{
					CMario* mario = (CMario*)coObj;
					if (mario->mState == EMarioState::ATTACK) {
						On_BEING_ATTACKED(nxCollision);
					}
					else mario->SwitchType(1);
				}
			}
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
			CMario* mario = (CMario*)coObj;
			if (nyCollision < 0 )
			{
				if (eState == EnemyState::LIVE)
				{
					SwitchState(EnemyState::WILL_DIE, GetTimeWillDie());
					mario->MarioAfterCollisionYWithEnemy();
				}
			}
			else mario->SwitchType(1);
			if(eType == EnemyType::RED_VENUS)
				mario->SwitchType(1);
		}
	}
}

void CEnemy::ProcessState_LIVE()
{
	vx = nx * GetSpeed_LIVE_X();
}

void CEnemy::ProcessState_BEING_KICK()
{
	vx = nx * DEFAULT_BEING_KICK_SPEED;
}

void CEnemy::ProcessState_BEING_HELD()
{
	LPGAMEOBJECT player = CScences::GetInstance()->Get(CGame::GetInstance()->GetCurrentSceneId())->GetPlayer();
	float l, t, r, b;
	player->GetBoundingBox(l, t, r, b);
	int nxPlayer = player->nx;
	if (nxPlayer == 1)
		x = player->x + (r - l);
	else
		x = player->x - KOOPAS_BBOX_WIDTH;
	vx = 0; vy = 0;
	y = (player->y);

	DebugOut(ToWSTR(std::to_string(y) + "\n").c_str());
}

void CEnemy::ProcessState_ACTION()
{
	vx = this->nx * BULLET_VENUS_SPEED;
}

void CEnemy::ProcessState_WILL_DIE()
{
	vx = 0;
	vy = 0;
}

void CEnemy::ProcessState_DIE()
{
	vx = 0;
	vy = 0;
	this->isHidden = true;
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (eState == EnemyState::LIVE)
		ProcessState_LIVE();
	else if(eState == EnemyState::BEING_ATTACKED)
		ProcessState_BEING_ATTACKED();
	else if (eState == EnemyState::BEING_KICK)
		ProcessState_BEING_KICK();
	else if (eState == EnemyState::BEING_HELD)
		ProcessState_BEING_HELD();
	else if (eState == EnemyState::JUMP)
		ProcessState_JUMP();
	else if (eState == EnemyState::FLY)
		ProcessState_FLY();
	else if (eState == EnemyState::ACTION)
		ProcessState_ACTION();
	else if (eState == EnemyState::WILL_DIE)
		ProcessState_WILL_DIE();
	else if (eState == EnemyState::DIE)
		ProcessState_DIE();

	vy += GetGravity() * dt;
	CGameObject::Update(dt, coObjects);
	CollisionWithObj(coObjects);
	AutoSwitchState();
}

string CEnemy::GetAnimationIdFromState()
{
	return DEFINE_ANI;
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

void CEnemy::SetState(EnemyState newState, DWORD timeNewState)
{
	x += GetSizeFromState(eState).x - GetSizeFromState(newState).x;
	y += GetSizeFromState(eState).y - GetSizeFromState(newState).y - 3; 

	beginState = GetTickCount();
	timeState = timeNewState;
	eState = newState;
}